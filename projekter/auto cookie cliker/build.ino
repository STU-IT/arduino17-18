#define MOUSE_PIN 3

void setup() {
  // put your setup code here, to run once:
  pinMode (MOUSE_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(MOUSE_PIN, HIGH);
  delay(100);
  digitalWrite(MOUSE_PIN, LOW);
  delay(100);
}
