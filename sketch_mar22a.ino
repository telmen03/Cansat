#define LDRPIN 2
void setup() {
 Serial.begin(115200);
 delay(1000);

}

void loop() {
  // put your main code here, to run repeatedly:
  int val = analogRead(LDRPIN);
  Serial.println("value: ");
  Serial.println(val);
delay(500);
}
  