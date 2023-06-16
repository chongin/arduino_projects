#include <DHT.h>

#define DHTPIN A5
#define DHTTYPE DHT11

#define HEARTBEAT_PIN A1

DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  //read_hearbeat();
  read_templature_humidity();
  delay(500);
}

void read_hearbeat()
{
  int val = analogRead(HEARTBEAT_PIN);
  Serial.println(val);
}

void read_templature_humidity()
{
  float h = dht.readHumidity();
  // Celsius (the default)
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  String str = String(h) + "," + String(t);
  Serial.println(str);

}
