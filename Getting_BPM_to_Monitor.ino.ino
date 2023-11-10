#include <Adafruit_BMP085.h>
#include <DHT.h>
#include <WiFi.h>
#include <ThingSpeak.h>

const char* ssid = "saru";   // your network SSID 
const char* password = "12345678";   // your network password

unsigned long myChannelNumber = 1864319;
const char* myWriteAPIKey = "2BDPDA602WO41Z7B";

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 30000;

// Create a sensor object
WiFiClient client;
#define DHTPIN 2           // DHT22 sensor pin
#define DHTTYPE DHT22      // DHT22 sensor type (changed from DHT11)

Adafruit_BMP085 bmp;       // BMP180 sensor object
DHT dht(DHTPIN, DHTTYPE);  // DHT22 sensor object

void setup() {
  Serial.begin(9600);
  dht.begin();  
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  wifiConnect();
  
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP180 sensor, check wiring!");
    while (1);
  }
}

void loop() {
  float temperature_bmp = bmp.readTemperature();  // Read temperature from BMP180 sensor
  float pressure = bmp.readPressure();            // Read pressure from BMP180 sensor
  float humidity = dht.readHumidity();            // Read humidity from DHT22 sensor (changed from DHT11)
  float temperature_dht = dht.readTemperature();  // Read temperature from DHT22 sensor (changed from DHT11)

  Serial.print("BMP180 Temperature: ");
  Serial.print(temperature_bmp);
  Serial.println(" °C");

  Serial.print("BMP180 Pressure: ");
  Serial.print(pressure);
  Serial.println(" Pa");

  Serial.print("DHT22 Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("DHT22 Temperature: ");
  Serial.print(temperature_dht);
  Serial.println(" °C");

  Serial.println("-------------------------");

  ThingSpeak.setField(1, pressure);
  ThingSpeak.setField(2, temperature_bmp);
  ThingSpeak.setField(3, humidity);
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  delay(2000);  // Delay between readings
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
