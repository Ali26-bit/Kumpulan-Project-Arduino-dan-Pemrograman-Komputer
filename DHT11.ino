
#include <Blynk.h>
#define BLYNK_TEMPLATE_ID "Temperatur"
#define BLYNK_DEVICE_NAME "sensor suhu DHT11"
#define BLYNK_FIRMARE_VERSION "0.1.0"

#define BLYNK_PRINT Serial

#include <DHT11.h>

#define DHTPN D2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200;)
  dht.begin();
  delay(100);

  BlynkEdgent.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  BlynkEdge.run();
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  Blynk.virtualWrite(v1, t);
  Blynk.virtualWrite(v2, h);
  }
