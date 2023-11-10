void setup() {
  Serial.begin(9600); // Initialize the Serial Monitor
}

void loop() {
  Serial.println("RF 315MHz protocol established. Message received from TX!");
  delay(1000); // Add a delay if you want to control the printing rate
}

