#include "Auger.h"

Auger::Auger(int relayNum, UINT32 IONum, UINT32 fullCap) :
    auger(relayNum), homeInput(IONum), home(homeInput), full(fullCap),
            loadedLast(true), loading(false), feeding(false), state(AUGER_IDLE)
{
}

void Auger::setState(augerState newState)
{
    if (newState == AUGER_LOADING_START && !loading)
    {
        return;
    }
    if (newState == AUGER_FEEDING_START && !feeding)
    {
        return;
    }
    state = newState;
}

void Auger::setForward()
{
    if (!full.Get())
    {
        auger.Set(Relay::kOff);
        state = AUGER_IDLE;
    }
    else
    {
        auger.Set(Relay::kForward);
    }
}

void Auger::doAuger()
{
    switch (state)
    {
    case AUGER_IDLE:
        auger.Set(Relay::kOff);
        loading = false;
        feeding = false;
        break;
    case AUGER_MANUALFWD:
        setForward();
        break;
    case AUGER_MANUALREV:
        auger.Set(Relay::kReverse);
        break;
    case AUGER_LOADING_START:
        loading = true;
        feeding = false;
        auger.Set(Relay::kOff);
        state = loadedLast ? AUGER_LOADING_WAITOFF : AUGER_LOADING_SKIPBUMP;
        loadedLast = true;
        break;
    case AUGER_LOADING_SKIPBUMP:
        auger.Set(Relay::kOff);
        if (!homeInput.Get())
        {
            home.Reset();
            home.Start();
            state = AUGER_LOADING_WAITBUMP;
        }
        else
        {
            state = AUGER_LOADING_WAITOFF;
        }
        break;
    case AUGER_LOADING_WAITBUMP:
        setForward();
        if (home.Get())
        {
            home.Reset();
            home.Start();
            state = AUGER_LOADING_WAITON;
        }
        break;
    case AUGER_LOADING_WAITOFF:
        setForward();
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
            setForward();
        }
        break;

    case AUGER_FEEDING_START:
        loading = false;
        feeding = true;
        auger.Set(Relay::kOff);
        state = !loadedLast ? AUGER_FEEDING_WAITOFF : AUGER_FEEDING_SKIPBUMP;
        loadedLast = false;
        break;
    case AUGER_FEEDING_SKIPBUMP:
        auger.Set(Relay::kOff);
        if (!homeInput.Get())
        {
            home.Reset();
            home.Start();
            state = AUGER_FEEDING_WAITBUMP;
        }
        else
        {
            state = AUGER_FEEDING_WAITOFF;
        }
        break;
    case AUGER_FEEDING_WAITBUMP:
        auger.Set(Relay::kReverse);
        if (home.Get())
        {
            home.Reset();
            home.Start();
            state = AUGER_FEEDING_WAITON;
        }
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
        setForward();
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
