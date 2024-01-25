//import of the libraries
#include "EspMQTTClient.h"
#include "DHT.h"

//definition of the variables
#define DHTPIN 21 
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//definition of the objects
EspMQTTClient client(
  "Xiaomi 13T Pro", //WiFI name
  "lullabi9(", //WiFi password
  "192.168.4.204",  // MQTT Broker server ip
  //"piccolo",   // MQTT Useraname
  //"pimpo", // MQTT Password
  "ESP32DHT", // Client name that uniquely identify your device
  1883 // The MQTT port, default to 1883. this line can be omitted
);


void setup()
{
  Serial.begin(9600);
  dht.begin();
  // Optional functionalities of EspMQTTClient
  client.enableDebuggingMessages(); // Enable debugging messages sent to serial output
  client.enableHTTPWebUpdater(); // Enable the web updater
  client.enableOTA(); // Enable OTA (Over The Air) updates
  client.enableLastWillMessage("ESP32DHT/lastwill", "I am going offline");  //It's possible to activate the retain flag by setting the third parameter to true
  Serial.println(client.isConnected());
}


// This function is called once everything is connected (Wifi and MQTT)
void onConnectionEstablished()
{
  // Subscribe to "building/controlTemperature" and display received message to Serial
  client.subscribe("building/controlTemperature", [](const String & payload) {
    Serial.println(payload);
  });

  // Subscribe to "building/controlTemperature/#" and display received message to Serial
  client.subscribe("building/controlTemperature/wildcard/#", 
                  [](const String & topic, const String & payload) {
    Serial.println("(From wildcard) topic: " + topic + ", payload: " + payload);
  });
}


void loop()
{
  client.loop();
  // Read relative humidity
  float hum = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float temp = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float far = dht.readTemperature(true);
  if (isnan(hum) || isnan(temp) || isnan(far)) { //If some value can be retrieved, notify a sensor fail
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(F("%  Temperature: "));
  Serial.print(temp);
  String stringTemperature = String(temp);
  client.publish("building/controlTemperature", stringTemperature); // It's possible to activate the retain flag by setting the third parameter to true
  delay(10000);  //set delay to 10 second between each reading
}

