#include <DHT.h>
#define LDRPIN 2
#define LDRPIN1 4

DHT dht(26, DHT11);

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
dht.begin();
 delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  float temp = dht.readTemperature();
float humidity = dht.readHumidity();
Serial.print("Temp: ");
Serial.print(temp);
Serial.print(" C ");
Serial.print("humidity: ");
Serial.print(humidity);
Serial.println(" % ");
 int val = analogRead(LDRPIN);
  Serial.println("Photo: ");
  Serial.println(val);
   int val1 = analogRead(LDRPIN1);
  Serial.println("Obstucle: ");
  Serial.println(val1);
delay(500);
delay(500);

}
