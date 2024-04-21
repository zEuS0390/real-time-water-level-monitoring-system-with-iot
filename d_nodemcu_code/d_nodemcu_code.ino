#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* WIFI_NETWORK_DEFAULT_SSID = "krx";
const char* WIFI_NETWORK_DEFAULT_PASSWORD = "taigamxmn";

const char* mqtt_server = "192.168.148.197";
const char* mqtt_username = "user";
const char* mqtt_password = "pass123";

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
    StaticJsonDocument<200> mainDoc;
    DeserializationError error = deserializeJson(mainDoc, jsonStr);
    if (!error) {
      if (mainDoc.containsKey("wifi_network_ssid") && mainDoc.containsKey("wifi_network_password")) {
        WiFi.disconnect();
        const char* ssid = mainDoc["wifi_network_ssid"];
        const char* password = mainDoc["wifi_network_password"];
        connectToWiFiNetwork(ssid, password);
      }
      client.publish("group11", jsonStr.c_str());
    } else {
      Serial.print("Parsing failed: ");
      Serial.println(error.c_str());
    }
  }
  delay(1000);
  client.loop();
}
