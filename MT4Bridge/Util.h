#pragma once

#include <iostream>

#include "Bar.h"
#include "Server.h"
#include "DateTime.h"
#include "Order.h"
#include "EventArgs.h"
#include "TimeFrame.h"
#include "SymbolInfo.h"

using namespace TradingAPI;

namespace MT4Bridge
{
    namespace Util
    {
        std::string convert(System::String^ str);
        System::String^ convert(const std::string& str);
        Server convert(MT4Server::Server^ srv);
        Server convert(MT4Server::MainServer^ srv);
        MT4Server::Timeframe convert(const TimeFrame tf);
        System::DateTime convert(DateTime& datetime);
        DateTime convert(System::DateTime datetime);
        Bar convert(MT4Server::Bar^ bar);
        Op convert(MT4Server::Op op);
        MT4Server::Op convert(Op op);
        Order convert(MT4Server::Order^ order);
        SymbolInfo convert(MT4Server::SymbolInfo info);
        EventArgs::QuoteEventArgs convert(MT4Server::QuoteEventArgs^ args);
    }
}
