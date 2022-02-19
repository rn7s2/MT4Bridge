#pragma once

#include "DLL.h"
#include "DateTime.h"

namespace MT4Bridge
{
    class DLL_EXPORT Bar
    {
    public:
        Bar();
        Bar(
            const DateTime& datetime,
            double High,
            double Open,
            double Low,
            double Close,
            double Volume
        );

    public:
        DateTime time;
        double High, Open, Low, Close, Volume;
    };
}
