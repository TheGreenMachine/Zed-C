#include "Conveyor.h"

void Conveyor::set(Relay::Value velocity)
{
    conveyor.Set(velocity);
}

