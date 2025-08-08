# OseeTally

**OseeTally** is a simple Arduino-compatible library for parsing Tally Light information from the **Osee GoStream Duet** video mixer over UDP.

## Features

- Supports up to 4 camera tally states
- Parses PGM (Program) and PVW (Preview) status
- Fires a callback on status change
- Designed for ESP32 / ESP8266

## Installation

Place this library into your `libraries` folder or install using the ZIP in the Arduino IDE.

## Example Usage

```cpp
#include <OseeTally.h>

OseeTally tally(IPAddress(192,168,0,87), 54321);

void onTallyChange(bool* pgm, bool* pvw) {
  for (int i = 0; i < 4; i++) {
    Serial.printf("Cam %d: PGM=%d, PVW=%d\n", i+1, pgm[i], pvw[i]);
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin("SSID", "PASS");
  while (WiFi.status() != WL_CONNECTED) delay(500);
  tally.begin();
  tally.setCallback(onTallyChange);
}

void loop() {
  tally.poll();
}
```

## License

MIT © 2025 Falcon
