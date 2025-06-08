#include <DHT.h>
#include <Arduino.h>
#include <ML8511.h>

#define ANALOGPIN  34
#define ENABLEPIN  27

ML8511 light(ANALOGPIN, ENABLEPIN);
DHT dht(18, DHT22);

void setup() {
  Serial.begin(115200);       // Start Serial first
  dht.begin();
  delay(2000);

  Serial.println(__FILE__);
  Serial.println("UV UltraViolet ML8511");
}

void loop() {
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temp) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Temp: ");
    Serial.print(temp);
    Serial.print(" C, Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  }

  light.enable();
  float UV = light.getUV();
  light.disable();

  Serial.print("UV Intensity: ");
  Serial.print(UV, 4);
  Serial.println(" mW/cm^2");

  // Optional: Convert to UV Index (approximate)
  float uvIndex = UV * 20.0;
  Serial.print("Approx. UV Index: ");
  Serial.println(uvIndex, 1);

  delay(2000);
}

