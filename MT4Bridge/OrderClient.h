#pragma once

#include "DLL.h"
#include "Order.h"
#include "QuoteClient.h"

namespace MT4Bridge
{
    class DLL_EXPORT OrderClient
    {
    public:
        OrderClient(QuoteClient& qc);
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
        Order OrderSend(
            const std::string& symbol,
            Op operation,
            double volume,
            double price,
            int slippage = 0,
            double stoploss = 0,
            double takeprofit = 0,
            const std::string& comment = std::string(),
            int magic = 0,
            DateTime expiration = DateTime("1900-01-01 00:00:00")
        );

    public:
#ifdef _MANAGED
        gcroot<TradingAPI::MT4Server::OrderClient^> oc;
#else
        intptr_t oc;
#endif
    };
}
