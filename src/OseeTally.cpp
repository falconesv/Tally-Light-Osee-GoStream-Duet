#include "OseeTally.h"

OseeTally::OseeTally(IPAddress listenIP, uint16_t listenPort)
    : ip(listenIP), port(listenPort) {}

void OseeTally::begin() {
    udp.begin(port);
    Serial.println("[Osee] UDP listening...");
}

bool OseeTally::getPGM(uint8_t cam) {
    return cam < 4 ? currentPGM[cam] : false;
}

bool OseeTally::getPVW(uint8_t cam) {
    return cam < 4 ? currentPVW[cam] : false;
}

void OseeTally::setCallback(void (*cb)(bool* pgm, bool* pvw)) {
    stateChangedCallback = cb;
}

void OseeTally::poll() {
    int packetSize = udp.parsePacket();
    while (packetSize) {
        uint8_t buf[64];
        int len = udp.read(buf, sizeof(buf));
        if (len >= 12) {
            OseeOk = true;
            uint8_t pvwMask = (buf[10] & 0xF0) >> 4;
            uint8_t pgmMask = (buf[11] & 0x0F);

            bool newPGM[4], newPVW[4];
            uint8_t newState = 0;

            for (int i = 0; i < 4; i++) {
                newPVW[i] = (pvwMask >> i) & 0x01;
                newPGM[i] = (pgmMask >> i) & 0x01;
                if (newPGM[i]) newState |= (1 << (i + 4));
                if (newPVW[i]) newState |= (1 << i);
            }

            if (newState != stateByte) {
                stateByte = newState;
                memcpy(currentPGM, newPGM, sizeof(currentPGM));
                memcpy(currentPVW, newPVW, sizeof(currentPVW));
                if (stateChangedCallback) stateChangedCallback(currentPGM, currentPVW);
            }
        }
        packetSize = udp.parsePacket();
    }
}
