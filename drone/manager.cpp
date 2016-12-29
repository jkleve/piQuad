#include <iostream>

#include <unistd.h>

#include "manager.h"
#include "pi_types.h"

Manager::Manager() : comms(100)
{
    // initialize communications w/ ground station
    ret_code_t comms_code = unknown;
    schedule = on;

    //thr = new boost::thread(boost::bind(&Comms::Comms, Comms));
    //boost::thread t(server); // TODO
    comms_code = comms.initialize();

    if (comms_code == success)
    {
        schedule = ready;
    }
    else
    {
        schedule = error;
    }

    #ifdef DEBUG
    std::cout << "-=| Manager ctor |=-" << std::endl;
    #endif // DEBUG
}

void Manager::initialize()
{
    // initialize gnc & motors
    #ifdef PI
    gnc.initialize();
    #endif // PI

    schedule = ready;

    #ifdef DEBUG
    std::cout << "-=| Manager init |=-" << std::endl;
    #endif // DEBUG
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
        comms.step();
        #ifdef PI
        gnc.step();
        #endif // PI

        usleep(50);
    }
}
