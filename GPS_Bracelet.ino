#include "GSM_MQTT.h"
#include "ublox.h"

#define SERVER_USERNAME "wearareyou"
#define SERVER_PASSWORD "acc0d85f125a4583b73558c32e988459"
#define GSM_RESET_PIN 2
#define GPS_RESET_PIN 6
#define TAMPER_PIN	12

bool readGPS = false;
// bool tampered = false;
// uint8_t lastLocation = 0;

// MQTT host address
String MQTT_HOST = "io.adafruit.com";
// MQTT port
String MQTT_PORT = "1883";

void GSM_MQTT::AutoConnect(void)
{
  connect(SERVER_USERNAME, SERVER_PASSWORD);  
}

// keep alive time 20 seconds
GSM_MQTT MQTT(20);

void setup()
{
  GPSConfig();  // configure GPS setting 
  pinMode(GSM_RESET_PIN, OUTPUT);
  pinMode(TAMPER_PIN, INPUT);
  digitalWrite(GSM_RESET_PIN, HIGH);
  delay(2000);
  digitalWrite(GSM_RESET_PIN, LOW);
  MQTT.disconnect();

  // initialize mqtt:
  // GSM modem should be connected to Harware Serial
  //  index =0;
  MQTT.begin();
  Serial.println("Starting");

}

void loop()
{
  if (MQTT.available() && readGPS)
  {
    MQTT.publish(SERVER_USERNAME "/feeds/GPS_streaming", gps_coordinate);
    Serial.print("Publishing: ");
    Serial.println(gps_coordinate);
 	  readGPS = false;
 	  delay(500);
  }
  MQTT.processing();  // processing response from MQTT
  delay(500);
}
