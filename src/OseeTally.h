#pragma once
#include <WiFiUdp.h>
#include <Arduino.h>
#include <IPAddress.h>

class OseeTally {
public:
    OseeTally(IPAddress listenIP, uint16_t port = 54321);
    void begin();
    void poll();
    void setCallback(void (*cb)(bool* pgm, bool* pvw));

    bool getPGM(uint8_t cam);  // cam: 0..3
    bool getPVW(uint8_t cam);

    bool OseeOk = false;

private:
    WiFiUDP udp;
    IPAddress ip;
    uint16_t port;
    uint8_t stateByte = 0;

    bool currentPGM[4] = {false};
    bool currentPVW[4] = {false};

    void (*stateChangedCallback)(bool*, bool*) = nullptr;
};
