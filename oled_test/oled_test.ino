#include "SSD1306.h"
#include "OLEDDisplayUi.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "images.h"

SSD1306  display(0x3c, D2, D1);

OLEDDisplayUi ui     (&display);

byte bud_state = 0;
byte sensorValue;

unsigned long last_millis = 0;

const byte img_width = 105;
const byte img_height = 60;

const char* ssid = "SUTD_ILP2";
const char* password = "sutd-acce55";
const char* mqtt_server = "128.199.79.47";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

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
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is acive low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      //client.publish("outTopic", "hello world");
      // ... and resubscribe
      //client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void drawFrame1(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  ui.disableIndicator();
  if (bud_state == 1) {
    display->drawXbm((128 - img_width) / 2, (64 - img_height) / 2, img_width, img_height, happy_1);
  }
  if (bud_state == 2) {
    display->drawXbm((128 - img_width) / 2, (64 - img_height) / 2, img_width, img_height, sad_1);
  }
  if (bud_state == 3) {
    display->drawXbm((128 - img_width) / 2, (64 - img_height) / 2, img_width, img_height, dead_1);
  }
  if (bud_state == 0) {
    display->drawXbm((128 - img_width) / 2, (64 - img_height) / 2, img_width, img_height, neutral_1);
  }
}

void drawFrame2(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  ui.disableIndicator();
  if (bud_state == 1) {
    display->drawXbm((128 - img_width) / 2, (64 - img_height) / 2, img_width, img_height, happy_2);
  }
  if (bud_state == 2) {
    display->drawXbm((128 - img_width) / 2, (64 - img_height) / 2, img_width, img_height, sad_2);
  }
  if (bud_state == 3) {
    display->drawXbm((128 - img_width) / 2, (64 - img_height) / 2, img_width, img_height, dead_2);
  }
  if (bud_state == 0) {
    display->drawXbm((128 - img_width) / 2, (64 - img_height) / 2, img_width, img_height, neutral_2);
  }
}

void drawFrame3(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  ui.disableIndicator();
  if (bud_state == 1) {
    display->drawXbm((128 - img_width) / 2, (64 - img_height) / 2, img_width, img_height, happy_3);
  }
  if (bud_state == 2) {
    display->drawXbm((128 - img_width) / 2, (64 - img_height) / 2, img_width, img_height, sad_3);
  }
  if (bud_state == 3) {
    display->drawXbm((128 - img_width) / 2, (64 - img_height) / 2, img_width, img_height, dead_3);
  }
  if (bud_state == 0) {
    display->drawXbm((128 - img_width) / 2, (64 - img_height) / 2, img_width, img_height, neutral_3);
  }

}

void drawFrame4(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  ui.disableIndicator();
  if (bud_state == 1) {
    display->drawXbm((128 - img_width) / 2, (64 - img_height) / 2, img_width, img_height, happy_4);
  }
  if (bud_state == 2) {
    display->drawXbm((128 - img_width) / 2, (64 - img_height) / 2, img_width, img_height, sad_4);
  }
  if (bud_state == 3) {
    display->drawXbm((128 - img_width) / 2, (64 - img_height) / 2, img_width, img_height, dead_4);
  }
  if (bud_state == 0) {
    display->drawXbm((128 - img_width) / 2, (64 - img_height) / 2, img_width, img_height, neutral_4);
  }
}

FrameCallback frames[] = { drawFrame1, drawFrame2, drawFrame3, drawFrame4};
int frameCount = 4;

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);
  Serial.begin(115200);
  Serial.println();

  display.init();
  display.flipScreenVertically();
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(ArialMT_Plain_10);
  display.drawString(64, 10, ssid);
  display.setFont(ArialMT_Plain_16);
  display.drawString(64, 24, "Connecting...");
  display.setFont(ArialMT_Plain_10);
  display.drawString(64, 44, "getbud.design");
  display.display();

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  
  display.clear();
  
  ui.setTargetFPS(30);
  ui.setFrames(frames, frameCount);
  ui.setTimePerFrame(200);
  ui.setTimePerTransition(0);

  bud_state = 0;

  ui.init();

  display.flipScreenVertically();
  last_millis = millis();
}

void loop() {
  int rawValue;
  unsigned long currentMillis = millis();
  rawValue = analogRead(A0);
  Serial.println(rawValue);
  sensorValue = map(rawValue, 1000, 300, 0, 100);
  int remainingTimeBudget = ui.update();

  if (remainingTimeBudget > 0) {
    if (!client.connected()) {
      reconnect();
    }
    client.loop();

    long now = millis();
    if (now - lastMsg > 2000) {
      lastMsg = now;
      snprintf (msg, 75, "%ld", sensorValue);
      client.publish("outTopic", msg);
    }

    if ( (sensorValue > 50) || (sensorValue < 10) ) {
      bud_state = 3;
    } else {
      bud_state = 1;
    }

    delay(remainingTimeBudget / 4);
  }
}
