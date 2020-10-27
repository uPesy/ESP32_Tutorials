#include "WiFi.h"

int etat =0;
hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
 
void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  etat = !etat;
  digitalWrite(2,etat);
  portEXIT_CRITICAL_ISR(&timerMux);
 
}
 
void setup() {
  pinMode(2,OUTPUT);
  Serial.begin(115200);
 
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1000000, true);
  timerAlarmEnable(timer);

  Serial.println("\n\nuPesy ESP32 Wroom DevKit v1");
  WiFi.mode(WIFI_STA);
}
 
void loop() {
  Serial.println("uPesy ESP32 Wroom DevKit v1 : WiFi Demo");
  Serial.println("[*] Scanning WiFi network");
  
    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();
    Serial.println("[*] Scan done");
    if (n == 0) {
        Serial.println("[-] No WiFi networks found");
    } else {
        Serial.print("[+] ");
        Serial.print(n);
        Serial.print(" WiFi networks found\n");
        for (int i = 0; i < n; ++i) {
            // Print SSID and RSSI for each network found
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            Serial.print(")");
            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
            delay(10);
        }
    }
    Serial.println("");

    // Wait a bit before scanning again
    delay(5000);
}
