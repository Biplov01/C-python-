#include <WiFi.h>
#include <ThingSpeak.h>

const char* ssid = "RAMESH_NTFiber";   // your network SSID 
const char* password = "9849981596";   // your network password

unsigned long myChannelNumber = 1864319;
const char* myWriteAPIKey = "2BDPDA602WO41Z7B";

const int gasSensorPin = A0;  // Analog pin connected to MQ6 sensor
const int ledPin = 9;        // Digital pin connected to LED

WiFiClient client;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  wifiConnect();
}

void loop() {
  int gasSensorValue = analogRead(gasSensorPin);  // Read analog value from gas sensor

  Serial.print("Gas Sensor Value: ");
  Serial.println(gasSensorValue);

  if (gasSensorValue > 200) {
    digitalWrite(ledPin, HIGH);  // Turn on the LED when gas is detected
    Serial.println("Gas Leakage Detected!");
  } else {
    digitalWrite(ledPin, LOW);   // Turn off the LED when no gas is detected
  }

  ThingSpeak.setField(1, gasSensorValue);  // Send gas sensor value to Field 1
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  delay(1000);  // Delay between readings
}

// Function to connect WiFi
void wifiConnect() {
  Serial.println("Connecting to WiFi!");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("WiFi connected.");
}
