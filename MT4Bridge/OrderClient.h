#pragma once

#include "DLL.h"
#include "Order.h"
#include "QuoteClient.h"

using namespace TradingAPI;

namespace MT4Bridge
{
    class DLL_EXPORT OrderClient
    {
    public:
        OrderClient(const QuoteClient& qc);
        Order OrderClose(
            const std::string& symbol,
            int ticket,
            double volume,
            double price,
            int slippage
        );
        void OrderCloseBy(
            const std::string& symbol,
            int ticket1,
            int ticket2
        );
        void OrderDelete(
            int ticket,
            Op type,
            const std::string& symbol,
            double volume,
            double price
        );
        void OrderModify(
            int ticket,
            const std::string& symbol,
            Op type,
            double volume,
            double price,
            double stoploss,
            double takeprofit,
            DateTime& expiration
        );
        void OrderMultipleCloseBy(const std::string& symbol);

    public:
#ifdef _MANAGED
        gcroot<MT4Server::OrderClient^> oc;
#else
        intptr_t oc;
#endif
    };
}
