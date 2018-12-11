#ifndef __MAIN_H_
#define __MAIN_H_

#define CONFIG_SPIFFS_PATH "/config.json"

#include <WiFiManager.h>

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

void loadConfig();
void setupWifiManager();
bool startWifiManager();
void saveConfig();

#endif // __MAIN_H_