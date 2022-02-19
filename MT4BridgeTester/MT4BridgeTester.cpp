#include <iostream>
#include <vector>
#include <fstream>
#include <windows.h>

#include "../MT4Bridge/Bar.h"
#include "../MT4Bridge/Server.h"
#include "../MT4Bridge/EventArgs.h"
#include "../MT4Bridge/QuoteClient.h"
#include "../MT4Bridge/SymbolInfo.h"

// 调用这个宏的语句为输出语句，可忽略
#define DUMP(x) std::cout << (#x) << " = " << (x) << std::endl;

namespace EventArgs
{
    DLL_EXPORT std::vector<EventArgs::QuoteEventArgs> quote_events;
}

// 这个类的成员函数是各种示例
class Demos
{
public:
    // Demos被创建时调用的构造函数，通过srv文件连接到MT4服务器
    Demos()
    {
        // 打开srv文件，获取服务器信息
        std::string file("demo.srv");
        MT4Bridge::Server srv(MT4Bridge::QuoteClient::LoadSrv(file));

        // 建立报价客户端对象
        qc = new MT4Bridge::QuoteClient(username, password, srv.host, srv.port);

        // 这几个参数作用请看文档
        qc->AutoReconnect = true;
        qc->CalculateTradeProps = true;
        qc->PathForSavingSrv = ".";

        // 建立连接
        qc->Connect();
    }

    // Demos被清除时调用的析构函数，断开连接，释放qc内存
    ~Demos()
    {
        qc->Disconnect();
        delete qc;
    }

    // 账户的基本信息，名字叫Account...的，都这样用
    void AccountBalance()
    {
        // 类似下面的为输出语句，不影响功能，可忽略
        // 注意，封装后这些C# .NET的Property变成了函数
        DUMP(qc->AccountBalance());
    }

    // 下载历史订单
    void DownloadOrderHistory()
    {
        std::vector<MT4Bridge::Order> history(
            qc->DownloadOrderHistory(
                MT4Bridge::DateTime("1900-01-01 00:00:00"),
                MT4Bridge::DateTime::Now()
            )
        );

        for (MT4Bridge::Order order : history) {
            DUMP(order.Ticket);
            DUMP(order.Symbol);
            DUMP(order.Profit);
            DUMP(order.OpenTime.format());
            DUMP(order.OpenPrice);
            DUMP((int)order.Type);
        }
    }

    void GetOpenedOrders()
    {
        std::vector<MT4Bridge::Order> history(qc->GetOpenedOrders());

        for (MT4Bridge::Order order : history) {
            DUMP(order.Ticket);
            DUMP(order.Symbol);
            DUMP(order.Profit);
            DUMP(order.OpenTime.format());
            DUMP(order.OpenPrice);
            DUMP((int)order.Type);
        }
    }

    // 下载历史报价
    void DownloadQuoteHistory()
    {
        std::vector<MT4Bridge::Bar> history(
            qc->DownloadQuoteHistory(
                "EURUSD",
                MT4Bridge::TimeFrame::M15,
                MT4Bridge::DateTime::Now(),
                60
            )
        );

        for (MT4Bridge::Bar bar : history) {
            // 类似下面的为输出语句，不影响功能，可忽略
            DUMP(bar.time.format());
            DUMP(bar.High);
            DUMP(bar.Open);
            DUMP(bar.Low);
            DUMP(bar.Close);
            DUMP(bar.Volume);
        }
    }

    // 直接法 获取实时报价，MT4 API工作不正常，弃用
    // 接口保留，以备升级
    void GetQuote()
    {
        for (int i = 0; i < 60; i++) {
            EventArgs::QuoteEventArgs quote(qc->GetQuote("EURUSD"));
            DUMP(quote.time.format());
            DUMP(quote.symbol);
            DUMP(quote.ask);
            DUMP(quote.bid);
            Sleep(2000);
        }
    }

    // 间接法 获取实时报价
    void RealTimeQuotes()
    {
        // 清空接收最新报价的vector
        int last_size = 0;
        EventArgs::quote_events.clear();

        // 订阅报价推送
        qc->Subscribe("EURUSD");
        while (true) {
            if (last_size != EventArgs::quote_events.size()) {
                for (int i = last_size; i < EventArgs::quote_events.size(); i++) {
                    DUMP(EventArgs::quote_events[i].time.format());
                    DUMP(EventArgs::quote_events[i].symbol);
                    DUMP(EventArgs::quote_events[i].ask);
                    DUMP(EventArgs::quote_events[i].bid);
                }
                last_size = EventArgs::quote_events.size();
            }
            Sleep(100);
        }
    }

    // 获取品种信息
    void GetSymbolInfo()
    {
        MT4Bridge::SymbolInfo info(qc->GetSymbolInfo("EURUSD"));
        // 类似下面的为输出语句，不影响功能，可忽略
        DUMP(info.Code);
        DUMP(info.ContractSize);
        DUMP(info.Currency);
        DUMP(info.Digits);
        DUMP((int)info.Execution);
        DUMP(info.FreezeLevel);
        DUMP(info.MarginCurrency);
        DUMP(info.MarginDivider);
        DUMP((int)info.MarginMode);
        DUMP(info.Point);
        DUMP((int)info.ProfitMode);
        DUMP(info.Spread);
        DUMP(info.StopsLevel);
        DUMP(info.SwapLong);
        DUMP(info.SwapShort);
    }

    // 测试延迟，基本没用
    void PingHost()
    {
        std::cout << "Latency to rn7s2.cn:" << std::endl;
        for (int i = 0; i < 4; i++)
            std::cout << "Attempt #" << i << ": " << qc->PingHost("rn7s2.cn") << "ms" << std::endl;
    }

    // 获取服务器版本号
    void ServerBuild()
    {
        std::cout << "Server build:" << qc->ServerBuild() << std::endl;
    }

private:
    MT4Bridge::QuoteClient* qc;
};

int main()
{
    Demos demos;
    //demos.AccountBalance();
    //demos.DownloadOrderHistory();
    //demos.GetOpenedOrders();
    //demos.DownloadQuoteHistory();
    //demos.GetQuote();
    //demos.RealTimeQuotes();
    //demos.GetSymbolInfo();
    //demos.PingHost();
    //demos.ServerBuild();
    return 0;
}
