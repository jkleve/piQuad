#pragma once

enum schedule_t
{
    on,
    ready,
    grounded,
    inFlight,
    error
};

enum retCode_t
{
    unknown,
    success,
    failed
};
