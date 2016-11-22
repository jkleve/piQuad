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

    private:
        schedule_t schedule;
        GNC gnc;
        Comms comms;
};
