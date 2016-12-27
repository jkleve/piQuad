#pragma once

enum schedule_t
{
    on,
    ready,
    grounded,
    inFlight,
    error
};

enum ret_code_t
{
    unknown,
    success,
    failed
};
