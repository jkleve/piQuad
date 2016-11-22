#include "COMMS.h"
#include "GNC.h"

enum schedule_t
{
    initialize,
    ready,
    grounded,
    inFlight,
    error
};

class Manager {
    public:
        Manager();
        ~Manager();

        void initialize();
        schedule_t getSchedule();

    private:
        GNC gnc;
        COMMS comms;
};
