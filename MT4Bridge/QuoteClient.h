#pragma once

#include "DLL.h"
#include "Bar.h"
#include "Server.h"
#include "Order.h"
#include "TimeFrame.h"
#include "EventArgs.h"
#include "DateTime.h"
#include "SymbolInfo.h"

namespace MT4Bridge
{
    enum class AccountType {
        Real,
        Contest,
        Demo
    };

    class DLL_EXPORT QuoteClient
    {
    public:
        QuoteClient();
        QuoteClient(
            const int username,
            const std::string& password,
            const std::string& host,
            const int port
        );
        static Server LoadSrv(const std::string& file_path);
        static Server LoadSrv(
            const std::string& file_path,
            std::vector<Server>& srv_list
        );
        static int PingHost(const std::string& host);
        void Connect();
        void Disconnect();
        std::vector<Order> DownloadOrderHistory(DateTime from, DateTime to);
        std::vector<Bar> DownloadQuoteHistory(
            const std::string& symbol,
            TimeFrame tf,
            DateTime end,
            int count
        );
        Order GetOpenedOrder(int ticket);
        std::vector<Order> GetOpenedOrders();
        EventArgs::QuoteEventArgs GetQuote(const std::string& symbol);
        SymbolInfo GetSymbolInfo(const std::string& symbol);
        int ServerBuild();
        DateTime ServerTime();
        double AccountBalance();
        double AccountCredit();
        double AccountEquity();
        double AccountFreeMargin();
        int AccountLeverage();
        double AccountMargin();
        std::string AccountName();
        double AccountProfit();
        AccountType AccountType();
        bool Connected();
        DateTime ConnectTime();
        std::string Host();
        bool IsInvestor();
        int Port();
        std::vector<std::string> Symbols();
        void Subscribe(const std::string& symbol);
        void Unsubscribe(const std::string& symbol);
        bool IsSubscribed(const std::string& symbol);

    public:
        bool AutoReconnect;
        bool CalculateTradeProps;
        std::string PathForSavingSrv;

#ifdef _MANAGED
        gcroot<TradingAPI::MT4Server::QuoteClient^> qc;
#else
        intptr_t qc;
#endif
    };
}
