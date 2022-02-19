#include "pch.h"
#include "Bar.h"
#include "DateTime.h"
#include "SymbolInfo.h"
#include "Util.h"

using namespace TradingAPI;
using namespace MT4Bridge;

std::string Util::convert(System::String^ str)
{
    std::string ret;
    array<wchar_t>^ arr = str->ToCharArray();
    for (int i = 0; i < arr->Length; i++)
        ret.push_back(arr[i]);
    return ret;
}

System::String^ MT4Bridge::Util::convert(const std::string& str)
{
    return gcnew System::String(str.c_str());
}

Server Util::convert(MT4Server::Server^ srv)
{
    return Server(convert(srv->Host), srv->Port);
}

Server Util::convert(MT4Server::MainServer^ srv)
{
    return Server(convert(srv->Host), srv->Port);
}

MT4Server::Timeframe Util::convert(const TimeFrame tf)
{
    return (MT4Server::Timeframe)tf;
}

System::DateTime Util::convert(DateTime& datetime)
{
    System::DateTime % res = System::DateTime();
    if (System::DateTime::TryParse(gcnew System::String(datetime.format().c_str()), res) != false)
        return res;
    else
        return System::DateTime::MinValue;
}

DateTime Util::convert(System::DateTime datetime)
{
    return DateTime(convert(datetime.ToString("yyyy-MM-dd HH:mm:ss")));
}

Bar Util::convert(MT4Server::Bar^ bar)
{
    Bar ret;
    ret.High = bar->High;
    ret.Open = bar->Open;
    ret.Low = bar->Low;
    ret.Close = bar->Close;
    ret.time = Util::convert(bar->Time);
    ret.Volume = bar->Volume;
    return ret;
}

Op MT4Bridge::Util::convert(MT4Server::Op op)
{
    return Op(op);
}

MT4Server::Op Util::convert(Op op)
{
    return MT4Server::Op(op);
}

Order MT4Bridge::Util::convert(MT4Server::Order^ order)
{
    Order ret;
    ret.ClosePrice = order->ClosePrice;
    ret.CloseTime = Util::convert(order->CloseTime);
    ret.Comment = Util::convert(order->Comment);
    ret.Commission = order->Commission;
    ret.Expiration = Util::convert(order->Expiration);
    ret.Lots = order->Lots;
    ret.MagicNumber = order->MagicNumber;
    ret.OpenPrice = order->OpenPrice;
    ret.OpenTime = Util::convert(order->OpenTime);
    ret.Profit = order->Profit;
    ret.RateClose = order->RateClose;
    ret.RateMargin = order->RateMargin;
    ret.RateOpen = order->RateOpen;
    ret.StopLoss = order->StopLoss;
    ret.Swap = order->Swap;
    ret.Symbol = Util::convert(order->Symbol);
    ret.TakeProfit = order->TakeProfit;
    ret.Ticket = order->Ticket;
    ret.Type = Util::convert(order->Type);
    return ret;
}

SymbolInfo Util::convert(MT4Server::SymbolInfo info)
{
    SymbolInfo ret;
    ret.Code = info.Code;
    ret.ContractSize = info.ContractSize;
    ret.Currency = Util::convert(info.Currency);
    ret.Digits = info.Digits;
    ret.Execution = Execution(info.Execution);
    ret.FreezeLevel = info.FreezeLevel;
    ret.MarginCurrency = Util::convert(info.MarginCurrency);
    ret.MarginDivider = info.MarginDivider;
    ret.MarginMode = MarginMode(info.MarginMode);
    ret.Point = info.Point;
    ret.ProfitMode = ProfitMode(info.ProfitMode);
    ret.Spread = info.Spread;
    ret.StopsLevel = info.StopsLevel;
    ret.SwapLong = info.SwapLong;
    ret.SwapShort = info.SwapShort;
    return ret;
}

EventArgs::QuoteEventArgs MT4Bridge::Util::convert(MT4Server::QuoteEventArgs^ args)
{
    EventArgs::QuoteEventArgs ret;
    ret.symbol = Util::convert(args->Symbol);
    ret.ask = args->Ask;
    ret.bid = args->Bid;
    ret.time = Util::convert(args->Time);
    return ret;
}
