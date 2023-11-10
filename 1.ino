#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

const char* ssid = "RAMESH_NTFiber";   // your network SSID
const char* password = "9849981596";   // your network password

unsigned long myChannelNumber = 2112706;
const char* myWriteAPIKey = "R8AUP1KHA41L5K0J";

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 30000;


// Create a sensor object
WiFiClient client;

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  wifiConnect();
}

void loop() {
  // Generate random value between 50 and 75
  int randomValue = random(60, 100);
  Serial.println("♥ A heartbeat happened, BPM:");
  Serial.println(randomValue);

  // Update ThingSpeak field with the random value
  ThingSpeak.setField(1, randomValue);
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  
  delay(9000);
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
