#include <Arduino.h>
#include "io.h"

/**
 * Return Twig_ structure data to String
 * Can be used to save in a File or debugging
 *
 */
String io_imu_to_string(struct twig_struct *twig_data)
{
  String data = "I," + String(twig_data->ts_micro) + ",";
  data += String(twig_data->gyro[0], 4) + ",";
  data += String(twig_data->gyro[1], 4) + ",";
  data += String(twig_data->gyro[2], 4) + ",";
  data += String(twig_data->accel[0], 4) + ",";
  data += String(twig_data->accel[1], 4) + ",";
  data += String(twig_data->accel[2], 4) + "\n";
  data += "M," + String(twig_data->ts_micro) + ",";
  data += String(twig_data->mag[0]) + ",";
  data += String(twig_data->mag[1]) + ",";
  data += String(twig_data->mag[2]) + "\n";
  data += "Q," + String(twig_data->ts_micro) + ",";
  data += String(twig_data->quat[3], 4) + ",";
  data += String(twig_data->quat[0], 4) + ",";
  data += String(twig_data->quat[1], 4) + ",";
  data += String(twig_data->quat[2], 4) + "\n";
  data += "L," + String(twig_data->ts_micro) + ",";
  data += String(twig_data->quat[3], 4) + ",";
  data += String(twig_data->quat[0], 4) + ",";
  data += String(twig_data->quat[1], 4) + ",";
  data += String(twig_data->quat[2], 4) + ",";
  data += String(twig_data->l_accel[0], 4) + ",";
  data += String(twig_data->l_accel[1], 4) + ",";
  data += String(twig_data->l_accel[2], 4) + "\n";
  data += "E," + String(twig_data->ts_micro) + ",";
  data += String(twig_data->quat[3], 4) + ",";
  data += String(twig_data->quat[0], 4) + ",";
  data += String(twig_data->quat[1], 4) + ",";
  data += String(twig_data->quat[2], 4) + ",";
  data += String(twig_data->e_accel[0], 4) + ",";
  data += String(twig_data->e_accel[1], 4) + ",";
  data += String(twig_data->e_accel[2], 4) + "\n";
  return data;
}

/**
 * @TODO - convert to return String rather than print serially
 */
void io_imu(float voltage, struct twig_struct *twig_data)
{
  Serial.print("Battery V: ");
  Serial.println(voltage);
  Serial.print("Accel: ");
  Serial.print("x: ");
  Serial.print(twig_data->accel[0]);
  Serial.print(" ");
  Serial.print("y: ");
  Serial.print(twig_data->accel[1]);
  Serial.print(" ");
  Serial.print("z: ");
  Serial.print(twig_data->accel[2]);
  Serial.println(" ");
  Serial.print("Gyro: ");
  Serial.print("x: ");
  Serial.print(twig_data->gyro[0]);
  Serial.print(" ");
  Serial.print("y: ");
  Serial.print(twig_data->gyro[1]);
  Serial.print(" ");
  Serial.print("z: ");
  Serial.print(twig_data->gyro[2]);
  Serial.println(" ");
  Serial.print("Mag: ");
  Serial.print("x: ");
  Serial.print(twig_data->mag[0]);
  Serial.print(" ");
  Serial.print("y: ");
  Serial.print(twig_data->mag[1]);
  Serial.print(" ");
  Serial.print("z: ");
  Serial.print(twig_data->mag[2]);
  Serial.println(" ");
  Serial.print("Heading: ");
  Serial.print("degrees: ");
  Serial.print(twig_data->heading);
  Serial.println(" ");
  Serial.print("Quaternion: ");
  Serial.print("x: ");
  Serial.print(twig_data->quat[0]);
  Serial.print(" ");
  Serial.print("y: ");
  Serial.print(twig_data->quat[1]);
  Serial.print(" ");
  Serial.print("z: ");
  Serial.print(twig_data->quat[2]);
  Serial.print(" ");
  Serial.print("w: ");
  Serial.print(twig_data->quat[3]);
  Serial.println(" ");
}

/**
 * @TODO - convert to return String rather than print serially
 */
// https://github.com/adafruit/Adafruit_AHRS/blob/55a9541375458a05522cc4deb1c542067e23926d/examples/calibration/calibration.ino#L81
void io_motion_cal(struct twig_struct *twig_data)
{
  // 'Raw' values to match expectation of MotionCal
  Serial.print("Raw:");
  Serial.print(int(twig_data->accel[0] * 8192 / 9.8));
  Serial.print(",");
  Serial.print(int(twig_data->accel[1] * 8192 / 9.8));
  Serial.print(",");
  Serial.print(int(twig_data->accel[2] * 8192 / 9.8));
  Serial.print(",");
  Serial.print(int(twig_data->gyro[0] * DEGREES_PER_RADIAN * 16));
  Serial.print(",");
  Serial.print(int(twig_data->gyro[1] * DEGREES_PER_RADIAN * 16));
  Serial.print(",");
  Serial.print(int(twig_data->gyro[2] * DEGREES_PER_RADIAN * 16));
  Serial.print(",");
  Serial.print(int(twig_data->mag[0] * 10));
  Serial.print(",");
  Serial.print(int(twig_data->mag[1] * 10));
  Serial.print(",");
  Serial.print(int(twig_data->mag[2] * 10));
  Serial.println("");

  // unified data
  Serial.print("Uni:");
  Serial.print(twig_data->accel[0]);
  Serial.print(",");
  Serial.print(twig_data->accel[1]);
  Serial.print(",");
  Serial.print(twig_data->accel[2]);
  Serial.print(",");
  Serial.print(twig_data->gyro[0], 4);
  Serial.print(",");
  Serial.print(twig_data->gyro[1], 4);
  Serial.print(",");
  Serial.print(twig_data->gyro[2], 4);
  Serial.print(",");
  Serial.print(twig_data->mag[0]);
  Serial.print(",");
  Serial.print(twig_data->mag[1]);
  Serial.print(",");
  Serial.print(twig_data->mag[2]);
  Serial.println("");
}

/**
 * @TODO - convert to return String rather than print serially
 */
void io_x_imu3_gui(struct twig_struct *twig_data)
{
  // https://x-io.co.uk/downloads/x-IMU3-User-Manual-v1.1.pdf (page #23-24)

  /*
  The following message examples are for a timestamp of 1 second (1,000,000 microseconds) and argument
  values of:
    1. Gyroscope X axis = 0
    2. Gyroscope Y axis = 0
    3. Gyroscope Z axis = 0
    4. Accelerometer X axis = 0
    5. Accelerometer Y axis = 0
    6. Accelerometer Z axis = 1

    ASCII example: I,1000000,0.0000,0.0000,0.0000,0.0000,0.0000,1.0000\r\n
  */
  Serial.print("I");
  Serial.print(",");
  Serial.print(twig_data->ts_micro);
  Serial.print(",");
  Serial.print(twig_data->gyro[0], 4);
  Serial.print(",");
  Serial.print(twig_data->gyro[1], 4);
  Serial.print(",");
  Serial.print(twig_data->gyro[2], 4);
  Serial.print(",");
  Serial.print(twig_data->accel[0], 4);
  Serial.print(",");
  Serial.print(twig_data->accel[1], 4);
  Serial.print(",");
  Serial.print(twig_data->accel[2], 4);
  Serial.println("");

  /*
    The following message examples are for a timestamp of 1 second (1,000,000 microseconds) and argument
    values of:
      1. Magnetometer X axis = 1
      2. Magnetometer Y axis = 0
      3. Magnetometer Z axis = 0

      ASCII example: M,1000000,1.0000,0.0000,0.0000\r\n
  */
  Serial.print("M");
  Serial.print(",");
  Serial.print(twig_data->ts_micro);
  Serial.print(",");
  Serial.print(twig_data->mag[0], 4);
  Serial.print(",");
  Serial.print(twig_data->mag[1], 4);
  Serial.print(",");
  Serial.print(twig_data->mag[2], 4);
  Serial.println("");

  /*
    The following message examples are for a timestamp of 1 second (1,000,000 microseconds) and argument
    values of:
      1. Quaternion W element = 1
      2. Quaternion X element = 0
      3. Quaternion Y element = 0
      4. Quaternion Z element = 0
    ASCII example: Q,1000000,1.0000,0.0000,0.0000,0.0000\r\n
  */
  Serial.print("Q");
  Serial.print(",");
  Serial.print(twig_data->ts_micro);
  Serial.print(",");
  Serial.print(twig_data->quat[3], 4);
  Serial.print(",");
  Serial.print(twig_data->quat[0], 4);
  Serial.print(",");
  Serial.print(twig_data->quat[1], 4);
  Serial.print(",");
  Serial.print(twig_data->quat[2], 4);
  Serial.println("");

  /*
    The following message examples are for a timestamp of 1 second (1,000,000 microseconds) and argument
    values of:
      1. Quaternion W element = 1
      2. Quaternion X element = 0
      3. Quaternion Y element = 0
      4. Quaternion Z element = 0
      5. Linear acceleration X axis = 0
      6. Linear acceleration Y axis = 0
      7. Linear acceleration Z axis = 0
    ASCII example: L,1000000,1.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000\r\n
  */
  Serial.print("L");
  Serial.print(",");
  Serial.print(twig_data->ts_micro);
  Serial.print(",");
  Serial.print(twig_data->quat[3], 4);
  Serial.print(",");
  Serial.print(twig_data->quat[0], 4);
  Serial.print(",");
  Serial.print(twig_data->quat[1], 4);
  Serial.print(",");
  Serial.print(twig_data->quat[2], 4);
  Serial.print(",");
  Serial.print(twig_data->l_accel[0], 4);
  Serial.print(",");
  Serial.print(twig_data->l_accel[1], 4);
  Serial.print(",");
  Serial.print(twig_data->l_accel[2], 4);
  Serial.println("");

  /*
    The following message examples are for a timestamp of 1 second (1,000,000 microseconds) and argument
    values of:
      1. Quaternion W element = 1
      2. Quaternion X element = 0
      3. Quaternion Y element = 0
      4. Quaternion Z element = 0
      5. Earth acceleration X axis = 0
      6. Earth acceleration Y axis = 0
      7. Earth acceleration Z axis = 0
    ASCII example: E,1000000,1.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000\r\n
  */
  Serial.print("E");
  Serial.print(",");
  Serial.print(twig_data->ts_micro);
  Serial.print(",");
  Serial.print(twig_data->quat[3], 4);
  Serial.print(",");
  Serial.print(twig_data->quat[0], 4);
  Serial.print(",");
  Serial.print(twig_data->quat[1], 4);
  Serial.print(",");
  Serial.print(twig_data->quat[2], 4);
  Serial.print(",");
  Serial.print(twig_data->e_accel[0], 4);
  Serial.print(",");
  Serial.print(twig_data->e_accel[1], 4);
  Serial.print(",");
  Serial.print(twig_data->e_accel[2], 4);
  Serial.println("");
}
