void setup() {
  Serial.begin(115200);
}
void loop() {
  static uint32_t lastPrint;
  uint32_t topLoop = micros();
  if (topLoop - lastPrint >= 2000000) {
    lastPrint = topLoop;
    Serial.println(topLoop);
  }
}
