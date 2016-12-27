#pragma once

#include <boost/thread.hpp>

#include "comms.h"
#include "gnc.h"
#include "pi_types.h"

class Manager {
    public:
        Manager();

        void initialize();
        void arm();
        void disarm();

        void run();

        schedule_t getSchedule();

        Comms comms;

    private:
        schedule_t schedule;
        GNC gnc;
};
