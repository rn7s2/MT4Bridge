#pragma once

#include "DLL.h"
#include <string>

namespace MT4Bridge
{
    enum class Execution {
        Request,
        Instant,
        Market
    };

    enum class MarginMode {
        Forex,
        CFD,
        Futures,
        CfdIndex,
        CfdLeverage
    };

    enum class ProfitMode {
        Forex,
        CFD,
        Futures
    };

    class DLL_EXPORT SymbolInfo
    {
    public:
        int Code;
        double ContractSize;
        std::string	Currency;
        int Digits;
        Execution Execution;
        int FreezeLevel;
        std::string MarginCurrency;
        double MarginDivider;
        MarginMode MarginMode;
        double Point;
        ProfitMode ProfitMode;
        int Spread;
        int StopsLevel;
        double SwapLong;
        double SwapShort;
    };
}
