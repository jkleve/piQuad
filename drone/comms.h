#include "pi_types.h"

class Comms
{
    public:
        Comms();
        retCode_t initialize();
        void step();
};
