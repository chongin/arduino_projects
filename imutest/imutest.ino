#include <Adafruit_LSM6DSOX.h>
#include <SparkFun_MMC5983MA_Arduino_Library.h> 
#include <Wire.h>
#include "Fusion.h" // absolute lifesaver!
#include "common.h"
#include "io.h"

Adafruit_LSM6DSOX sox;
SFE_MMC5983MA myMag;

FusionEuler euler;
FusionQuaternion quaternion;
FusionAhrs ahrs;

struct twig_struct twig_data = {0};

#define IMU_SAMPLE_RATE (100) // lie about sample rate for nicer filtering


uint32_t magX = 0;
uint32_t magY = 0;
uint32_t magZ = 0;
double normalizedX = 0;
double normalizedY = 0;
double normalizedZ = 0;
double heading = 0;
float time_now = 0.0f;
float time_pre = 0.0f;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  if (!sox.begin_I2C()) {
    Serial.println("Failed to find LSM6DSOX chip");
    while (1) {
      delay(10);
    }
  }

  Serial.println("LSM6DSOX Found!");
  sox.setAccelRange(LSM6DS_ACCEL_RANGE_4_G);
  sox.setAccelDataRate(LSM6DS_RATE_104_HZ);

  sox.setGyroRange(LSM6DS_GYRO_RANGE_500_DPS );
  sox.setGyroDataRate(LSM6DS_RATE_104_HZ);

  Wire.begin();
  Wire.setClock(400000); // max i2c bus speed = 400KHz
  
  if (myMag.begin() == false)
  {
      Serial.println("MMC5983MA did not respond - check your wiring. Freezing.");
      while (true)
          ;
  }

  myMag.softReset();
  Serial.println("MMC5983MA connected");


  FusionAhrsInitialise(&ahrs);

  // Set AHRS algorithm settings
  const FusionAhrsSettings settings = {
      .gain = 0.5f,                            // This also needs to be validated
      .accelerationRejection = 10.0f,          // This might need to be changed for slapshots!
      .magneticRejection = 20.0f,              // This also needs to be validated - we are using a magnetometer
      .rejectionTimeout = 5 * IMU_SAMPLE_RATE, /* 5 seconds */
  };
  FusionAhrsSetSettings(&ahrs, &settings);

  Serial.println("Fushion Inited");
  delay(1000);
}


void loop() {
  // put your main code here, to run repeatedly:

  sensors_event_t accel;
  sensors_event_t gyro;
  sensors_event_t temp;
  sox.getEvent(&accel, &gyro, &temp);

  uint32_t rawValueX = 0;
  uint32_t rawValueY = 0;
  uint32_t rawValueZ = 0;
  double scaledX = 0;
  double scaledY = 0;
  double scaledZ = 0;
  double heading = 0;

  // Read all three channels simultaneously
  myMag.getMeasurementXYZ(&rawValueX, &rawValueY, &rawValueZ);
  scaledX = (double)rawValueX - 131072.0;
  scaledX /= 131072.0;
  
  scaledY = (double)rawValueY - 131072.0;
  scaledY /= 131072.0;
  
  scaledZ = (double)rawValueZ - 131072.0;
  scaledZ /= 131072.0;
  
  // Magnetic north is oriented with the Y axis
  // Convert the X and Y fields into heading using atan2 (Arc Tangent 2)
  heading = atan2(scaledX, 0 - scaledY);
  
  // atan2 returns a value between +PI and -PI
  // Convert to degrees
  heading /= PI;
  heading *= 180;
  heading += 180;

  normalizedX = scaledX * 8;
  normalizedY = scaledY * 8;
  normalizedZ = scaledZ * 8;

  const FusionVector accelerometer = {accel.acceleration.x, accel.acceleration.y, accel.acceleration.z}; // accelerometer data in g
  const FusionVector gyroscope = {gyro.gyro.x, gyro.gyro.y, gyro.gyro.z};        // gyroscope data in degrees/s
  const FusionVector magnetometer = {-(float)normalizedX, -(float)normalizedY, -(float)normalizedZ};  // magnetometer data in arbitrary units - Gauss  

  time_now = micros();
  float deltaTime = (time_now - time_pre) / 1000000.0f; // time difference in seconds
  time_pre = time_now;

  FusionAhrsUpdate(&ahrs, gyroscope, accelerometer, magnetometer, deltaTime);
  quaternion = FusionAhrsGetQuaternion(&ahrs);
  euler = FusionQuaternionToEuler(quaternion);

  const FusionVector linear = FusionAhrsGetLinearAcceleration(&ahrs);
  const FusionVector earth = FusionAhrsGetEarthAcceleration(&ahrs);

  twig_data.yaw = constrain(map(euler.angle.yaw + 180, 0, 360, 0, 256), 0, 255);
  twig_data.pitch = constrain(map(euler.angle.pitch + 180, 0, 360, 0, 256), 0, 255);
  twig_data.roll = constrain(map(euler.angle.roll + 180, 0, 360, 0, 256), 0, 255);

  Serial.print("roll:");
  Serial.print(twig_data.roll);
  Serial.print(", pitch:");
  Serial.print(twig_data.pitch);
  Serial.print(", yaw:");
  Serial.println(twig_data.yaw);
  // This data is only really needed for training the MLC/FSM
  // although conceptually we should be able to do the same
  // with the yaw, pitch, roll changes over time?
  twig_data.accel[0] = accelerometer.axis.x;
  twig_data.accel[1] = accelerometer.axis.y;
  twig_data.accel[2] = accelerometer.axis.z;

  twig_data.gyro[0] = gyroscope.axis.x;
  twig_data.gyro[1] = gyroscope.axis.y;
  twig_data.gyro[2] = gyroscope.axis.z;

  twig_data.mag[0] = magnetometer.axis.x;
  twig_data.mag[1] = magnetometer.axis.y;
  twig_data.mag[2] = magnetometer.axis.z;

  twig_data.quat[0] = quaternion.element.x;
  twig_data.quat[1] = quaternion.element.y;
  twig_data.quat[2] = quaternion.element.z;
  twig_data.quat[3] = quaternion.element.w;

  twig_data.l_accel[0] = linear.axis.x;
  twig_data.l_accel[1] = linear.axis.y;
  twig_data.l_accel[2] = linear.axis.z;

  twig_data.e_accel[0] = earth.axis.x;
  twig_data.e_accel[1] = earth.axis.y;
  twig_data.e_accel[2] = earth.axis.z;

  twig_data.heading = heading;

  twig_data.ts_micro = time_now;

  io_x_imu3_gui(&twig_data);

  delay(100);
}
