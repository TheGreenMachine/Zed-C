#include "Auger.h"

Auger::Auger(int relayNum, UINT32 IONum) :
    auger(relayNum), homeInput(IONum), home(homeInput)
{
}

void Auger::setState(augerState newState)
{
    if (newState == AUGER_LOADING_START && (state == AUGER_LOADING_WAITOFF
            || state == AUGER_LOADING_WAITON))
    {
        return;
    }
    if (newState == AUGER_FEEDING_START && (state == AUGER_FEEDING_WAITOFF
            || state == AUGER_FEEDING_WAITON))
    {
        return;
    }
    state = newState;
}

void Auger::doAuger()
{
    switch (state)
    {
    case AUGER_IDLE:
        auger.Set(Relay::kOff);
        break;
    case AUGER_MANUALFWD:
        auger.Set(Relay::kForward);
        break;
    case AUGER_MANUALREV:
        auger.Set(Relay::kReverse);
        break;
    case AUGER_LOADING_START:
        auger.Set(Relay::kForward);
        state = AUGER_LOADING_WAITOFF;
        break;
    case AUGER_LOADING_WAITOFF:
        auger.Set(Relay::kForward);
        if (!homeInput.Get())
        {
            home.Reset();
            home.Start();
            state = AUGER_LOADING_WAITON;
        }
        break;
    case AUGER_LOADING_WAITON:
        if (home.Get())
        {
            auger.Set(Relay::kOff);
            state = AUGER_IDLE;
        }
        else
        {
            auger.Set(Relay::kForward);
        }
        break;
    case AUGER_FEEDING_START:
        auger.Set(Relay::kReverse);
        state = AUGER_FEEDING_WAITOFF;
        break;
    case AUGER_FEEDING_WAITOFF:
        auger.Set(Relay::kReverse);
        if (!homeInput.Get())
        {
            home.Reset();
            home.Start();
            state = AUGER_FEEDING_WAITON;
        }
        break;
    case AUGER_FEEDING_WAITON:
        if (home.Get())
        {
            auger.Set(Relay::kOff);
            state = AUGER_IDLE;
        }
        else
        {
            auger.Set(Relay::kReverse);
        }
        break;
    case AUGER_OVERRIDE_FORWARD:
        auger.Set(Relay::kForward);
        break;
    case AUGER_OVERRIDE_REVERSE:
        auger.Set(Relay::kReverse);
        break;
    default:
        auger.Set(Relay::kOff);
        state = AUGER_IDLE;
        break;
    }
}
