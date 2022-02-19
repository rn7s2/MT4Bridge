#include "pch.h"
#include "Util.h"
#include "OrderClient.h"

using namespace TradingAPI;
using namespace MT4Bridge;

OrderClient::OrderClient(const QuoteClient& qc)
{
    oc = gcnew MT4Server::OrderClient(qc.qc);
}

Order OrderClient::OrderClose(
    const std::string& symbol,
    int ticket,
    double volume,
    double price,
    int slippage
)
{
    return Util::convert(oc->OrderClose(
                             Util::convert(symbol),
                             ticket,
                             volume,
                             price,
                             slippage
                         ));
}

void OrderClient::OrderCloseBy(
    const std::string& symbol,
    int ticket1,
    int ticket2
)
{
    oc->OrderCloseBy(Util::convert(symbol), ticket1, ticket2);
}

void OrderClient::OrderDelete(
    int ticket,
    Op type,
    const std::string& symbol,
    double volume,
    double price
)
{
    oc->OrderDelete(
        ticket,
        Util::convert(type),
        Util::convert(symbol),
        volume,
        price
    );
}

void OrderClient::OrderModify(
    int ticket,
    const std::string& symbol,
    Op type,
    double volume,
    double price,
    double stoploss,
    double takeprofit,
    DateTime& expiration
)
{
    oc->OrderModify(
        ticket,
        Util::convert(symbol),
        Util::convert(type),
        volume,
        price,
        stoploss,
        takeprofit,
        Util::convert(expiration)
    );
}

void OrderClient::OrderMultipleCloseBy(const std::string& symbol)
{
    oc->OrderMultipleCloseBy(Util::convert(symbol));
}
