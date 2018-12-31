#ifndef __MAIN_HPP_
#define __MAIN_HPP_

#include <Arduino.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

const char* otaPassword = "aircon";

#ifdef HARDWARE_V01
#define SWAP_PINS false
#endif

#ifdef HARDWARE_V02
#define SWAP_PINS true
#endif

#ifndef SWAP_PINS
#define HARDWARE_V02
#define SWAP_PINS true
#endif

#define DEBUG_BAUD_RATE 115200

// We'll look for a HIGH signal on this pin to decide if the heatpump unit is
// powering us
#define HEATPUMP_DETECT_PIN 4
// We assume a logic-level shift chip's "enable" or OE pin is wired here with a
// pulldown resistor. We'll output HIGH once we're ready to talk to the
// heatpump.
#define HEATPUMP_ENABLE_PIN 5
// We look for a 3-second LOW value on this pin to trigger a full reset of all
// settings.
#define CLEAR_SETTINGS_PIN 12

HardwareSerial* DebugSerial = &Serial;

bool heatPumpDetected = false;
bool detectHeatPump();

#define CONFIG_SPIFFS_PATH "/config.json"

#include <WiFiManager.h>
#include <Bounce2.h>

#ifndef WIFIMANAGER_AP_PASSWORD
#define WIFIMANAGER_AP_PASSWORD "espaircon"
#endif

#define MAX_LENGTH_MQTT_HOST 128
#define MAX_LENGTH_MQTT_PORT 6
#define MAX_LENGTH_MQTT_USERNAME 64
#define MAX_LENGTH_MQTT_PASSWORD 64
#define MAX_LENGTH_MQTT_TOPIC_PREFIX 32

typedef struct {
    char mqtt_host[MAX_LENGTH_MQTT_HOST] = "";
    char mqtt_port[MAX_LENGTH_MQTT_PORT] = "8080";
    char mqtt_username[MAX_LENGTH_MQTT_USERNAME] = "";
    char mqtt_password[MAX_LENGTH_MQTT_PASSWORD] = "";
    char mqtt_topic_prefix[MAX_LENGTH_MQTT_TOPIC_PREFIX] = "";
} Settings;

WiFiManagerParameter *custom_mqtt_host;
WiFiManagerParameter *custom_mqtt_port;
WiFiManagerParameter *custom_mqtt_username;
WiFiManagerParameter *custom_mqtt_password;
WiFiManagerParameter *custom_mqtt_topic_prefix;
WiFiManager *wifiManager;

Settings settings;

char mqtt_topic_info[128];

char mqtt_topic_availability[128];
char mqtt_topic_power_state[128];
char mqtt_topic_mode_state[128];
char mqtt_topic_temperature_state[128];
char mqtt_topic_fan_state[128];
char mqtt_topic_vane_state[128];
char mqtt_topic_current_temperature_state[128];

char mqtt_topic_power_command[128];
char mqtt_topic_mode_command[128];
char mqtt_topic_temperature_command[128];
char mqtt_topic_fan_command[128];
char mqtt_topic_vane_command[128];

Bounce clearSettingsButton;
bool shouldStartConfigAP = false;
bool shouldResetSettings = false;

void setupClearSettingsButtonHandler();
void loadConfig();
void setupWifiManager();
bool startWifiManager();
void saveConfig();

void handleClearSettingsButton();

bool validatePowerValue(const char* value);
bool validateModeValue(const char* value);
bool validateTemperatureValue(const char* value);
bool validateFanValue(const char* value);
bool validateVaneValue(const char* value);

void publishSystemBootInfo();
void publishSystemStatus();

#endif // __MAIN_HPP_
