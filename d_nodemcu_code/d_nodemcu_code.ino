#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* WIFI_NETWORK_DEFAULT_SSID = "krx";
const char* WIFI_NETWORK_DEFAULT_PASSWORD = "taigamxmn";

const char* mqtt_server = "192.168.148.197";
const char* mqtt_username = "user";
const char* mqtt_password = "pass123";

const char* mqtt_topic_rain = "group11/rain";
const char* mqtt_topic_water = "group11/water";
const char* mqtt_topic_distance = "group11/distance";

WiFiClient espClient;
PubSubClient client(espClient); 

void connectToWiFiNetwork(const char* ssid, const char* password) {
  // Your existing code for connecting to WiFi network
   delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("successfully connected to MQTT broker");
      // Once connected, publish an announcement...
      // ... and resubscribe
      // client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(9600);
  connectToWiFiNetwork(WIFI_NETWORK_DEFAULT_SSID, WIFI_NETWORK_DEFAULT_PASSWORD);
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  if (Serial.available() > 0) {
    String jsonStr = Serial.readStringUntil('\n');
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, jsonStr);
    if (!error) {

      if (doc.containsKey("wifi_network_ssid") && doc.containsKey("wifi_network_password")) {
        WiFi.disconnect();
        const char* ssid = doc["wifi_network_ssid"];
        const char* password = doc["wifi_network_password"];
        connectToWiFiNetwork(ssid, password);
      }

      if (doc.containsKey("group11/rain") || doc.containsKey("group11/water") || doc.containsKey("group11/distance")) {
        // Extract rain and water values
        int rainValue = doc["group11/rain"];
        int waterValue = doc["group11/water"];
        int distanceValue = doc["group11/distance"];
        
        // Publish the values to MQTT topics
        char rainBuffer[10];
        char waterBuffer[10];
        char distanceBuffer[10];
        itoa(rainValue, rainBuffer, 10);
        itoa(waterValue, waterBuffer, 10);
        itoa(distanceValue, distanceBuffer, 10);
        
        client.publish(mqtt_topic_rain, rainBuffer);
        client.publish(mqtt_topic_water, waterBuffer);
        client.publish(mqtt_topic_distance, distanceBuffer);
      }
      
    } else {
      Serial.print("Parsing failed: ");
      Serial.println(error.c_str());
    }
  }
  delay(1000);
  client.loop();
}