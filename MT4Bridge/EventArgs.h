#pragma once

#include <string>
#include <vector>
#include "DLL.h"
#include "DateTime.h"

namespace EventArgs
{
    class DLL_EXPORT QuoteEventArgs
    {
    public:
        std::string symbol;
        double ask, bid;
        MT4Bridge::DateTime time;
    };
}
