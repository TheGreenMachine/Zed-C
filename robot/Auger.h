#ifndef AUGER_H
#define AUGER_H
#include "WPILib.h"

class Auger
{
public:
    Auger(int relayNum, UINT32 IONum, UINT32 fullCap);
    enum augerState
    {
        AUGER_IDLE,
        AUGER_MANUALFWD,
        AUGER_MANUALREV,
        AUGER_LOADING_START,
        AUGER_LOADING_SKIPBUMP,
        AUGER_LOADING_WAITBUMP,
        AUGER_LOADING_WAITON,
        AUGER_LOADING_WAITOFF,
        AUGER_FEEDING_START,
        AUGER_FEEDING_SKIPBUMP,
        AUGER_FEEDING_WAITBUMP,
        AUGER_FEEDING_WAITON,
        AUGER_FEEDING_WAITOFF,
        AUGER_OVERRIDE_FORWARD,
        AUGER_OVERRIDE_REVERSE
    };
    void doAuger();
    void setState(augerState);
    void setForward();
private:
    Relay auger;
    DigitalInput homeInput;
    Counter home;
    DigitalInput full;
    bool loadedLast;
    bool loading;
    bool feeding;
    augerState state;

};

#endif
