#include "manager.h"
#include "pi_types.h"

Manager::Manager()
{
    // initialize communications w/ ground station
    retCode_t comms_code = unknown;
    schedule = on;
    comms_code = comms.initialize();

    if (comms_code == success)
    {
        schedule = ready;
    }
    else
    {
        schedule = error;
    }
}

void Manager::initialize()
{
    // initialize gnc & motors
    gnc.initialize();
    schedule = ready;
}

void Manager::arm()
{
    // allow user to request liftoff
    schedule = grounded;
}

void Manager::disarm()
{
    // disable motor control from user.
    schedule = ready;
}

void Manager::run()
{
    for (;;)
    {
        gnc.step();
    }
}
