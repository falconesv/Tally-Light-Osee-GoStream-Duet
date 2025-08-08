#include <WiFi.h>
#include <OseeTally.h>

const char* ssid = "YourSSID";
const char* pass = "YourPASS";

OseeTally oseeTally(IPAddress(192,168,0,87), 54321);

void onTallyChange(bool* pgm, bool* pvw) {
  for (int i = 0; i < 4; i++) {
    Serial.printf("Cam %d: PGM=%d, PVW=%d\n", i+1, pgm[i], pvw[i]);
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  oseeTally.begin();
  oseeTally.setCallback(onTallyChange);
}

void loop() {
  oseeTally.poll();
}
