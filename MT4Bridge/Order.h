#pragma once

#include "DateTime.h"

namespace MT4Bridge
{
    enum class Op {
        Buy,
        Sell,
        BuyLimit,
        SellLimit,
        BuyStop,
        SellStop,
        Balance,
        Credit
    };

    class DLL_EXPORT Order
    {
    public:
        double ClosePrice;
        DateTime CloseTime;
        std::string Comment;
        double Commission;
        DateTime Expiration;
        double Lots;
        int MagicNumber;
        double OpenPrice;
        DateTime OpenTime;
        double Profit;
        double RateClose;
        double RateMargin;
        double RateOpen;
        double StopLoss;
        double Swap;
        std::string Symbol;
        double TakeProfit;
        int Ticket;
        Op Type;
    };
}
