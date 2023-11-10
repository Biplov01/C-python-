const int gasSensorPin = A0;  // Analog pin connected to MQ6 sensor
const int ledPin = 9;        // Digital pin connected to LED

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(gasSensorPin);  // Read analog value from gas sensor
  
  Serial.printf("Gas Sensor Value: %d", sensorValue);

  if (sensorValue > 200) {
    digitalWrite(ledPin, HIGH);  // Turn on the LED when gas is detected
    Serial.println("Gas Leakage Detected!");
  } else
		digitalWrite(ledPin, LOW);   // Turn off the LED when no gas is detected

  delay(1000);  // Delay between readings
}
