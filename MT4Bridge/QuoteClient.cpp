#include "pch.h"
#include "Util.h"
#include "QuoteClient.h"

using namespace TradingAPI;
using namespace MT4Bridge;

namespace EventArgs
{
    extern DLL_EXPORT std::vector<QuoteEventArgs> quote_events;
}

QuoteClient::QuoteClient()
{
    qc = gcnew MT4Server::QuoteClient();
}

QuoteClient::QuoteClient(
    const int username,
    const std::string& password,
    const std::string& host,
    const int port
)
{
    qc = gcnew MT4Server::QuoteClient(
             username,
             gcnew System::String(password.c_str()),
             gcnew System::String(host.c_str()),
             port
         );
}

Server QuoteClient::LoadSrv(const std::string& file_path)
{
    return Util::convert(MT4Server::QuoteClient::LoadSrv(gcnew System::String(file_path.c_str())));
}

Server QuoteClient::LoadSrv(
    const std::string& file_path,
    std::vector<Server>& srv_list
)
{
    srv_list.clear();

    MT4Server::MainServer^ cli_srv;
    array<MT4Server::Server>^ cli_srv_list;
    cli_srv = MT4Server::QuoteClient::LoadSrv(
                  gcnew System::String(file_path.c_str()),
                  cli_srv_list
              );

    for (int i = 0; i < cli_srv_list->Length; i++)
        srv_list.push_back(Util::convert(cli_srv_list[i]));

    return Util::convert(cli_srv);
}

int QuoteClient::PingHost(const std::string& host)
{
    std::cout << "Ping " << host << " ..." << std::endl;
    return MT4Server::QuoteClient::PingHost(Util::convert(host));
}

void QuoteClient::Connect()
{
    qc->SetAutoReconnect(this->AutoReconnect);
    qc->CalculateTradeProps = this->CalculateTradeProps;
    qc->PathForSavingSrv = Util::convert(this->PathForSavingSrv);
    System::Console::WriteLine("Establishing connection with " + qc->Host + "...");
    try {
        qc->Connect();
    } catch (System::Exception^ e) {
        System::Console::WriteLine(e->ToString());
    }
    System::Console::WriteLine("Connection established, server build: " + qc->ServerBuild);

    //服务器时间API工作不正常
    //while (qc->ServerTime == System::DateTime::MinValue)
    //	System::Threading::Thread::Sleep(10);
    //System::Console::WriteLine("，服务器时间" + qc->ServerTime.ToString("yyyy-MM-dd HH:mm:ss"));
}

void QuoteClient::Disconnect()
{
    System::Console::WriteLine("Disconnecting...");
    qc->Disconnect();
}

std::vector<Order> QuoteClient::DownloadOrderHistory(DateTime from, DateTime to)
{
    std::vector<Order> ret;
    array<MT4Server::Order^>^ arr = qc->DownloadOrderHistory(
                                        Util::convert(from),
                                        Util::convert(to)
                                    );
    for (int i = 0; i < arr->Length; i++)
        ret.push_back(Util::convert(arr[i]));
    return ret;
}

std::vector<Bar> QuoteClient::DownloadQuoteHistory(
    const std::string& symbol,
    TimeFrame tf,
    DateTime end,
    int count
)
{
    std::vector<Bar> ret;
    array<MT4Server::Bar>^ arr = qc->DownloadQuoteHistory(
                                     gcnew System::String(symbol.c_str()),
                                     Util::convert(tf),
                                     Util::convert(end),
                                     count
                                 );
    for (int i = 0; i < arr->Length; i++)
        ret.push_back(Util::convert(arr[i]));
    return ret;
}

Order MT4Bridge::QuoteClient::GetOpenedOrder(int ticket)
{
    return Util::convert(qc->GetOpenedOrder(ticket));
}

std::vector<Order> MT4Bridge::QuoteClient::GetOpenedOrders()
{
    std::vector<Order> ret;
    array<MT4Server::Order^>^ arr = qc->GetOpenedOrders();
    for (int i = 0; i < arr->Length; i++)
        ret.push_back(Util::convert(arr[i]));
    return ret;
}

EventArgs::QuoteEventArgs MT4Bridge::QuoteClient::GetQuote(const std::string& symbol)
{
    return Util::convert(qc->GetQuote(Util::convert(symbol)));
}

SymbolInfo QuoteClient::GetSymbolInfo(const std::string& symbol)
{
    return Util::convert(qc->GetSymbolInfo(Util::convert(symbol)));
}

int QuoteClient::ServerBuild()
{
    return qc->ServerBuild;
}

DateTime QuoteClient::ServerTime()
{
    return Util::convert(qc->ServerTime);
}

double MT4Bridge::QuoteClient::AccountBalance()
{
    return qc->AccountBalance;
}

double MT4Bridge::QuoteClient::AccountCredit()
{
    return qc->AccountCredit;
}

double MT4Bridge::QuoteClient::AccountEquity()
{
    return qc->AccountEquity;
}

double MT4Bridge::QuoteClient::AccountFreeMargin()
{
    return qc->AccountFreeMargin;
}

int MT4Bridge::QuoteClient::AccountLeverage()
{
    return qc->AccountLeverage;
}

double MT4Bridge::QuoteClient::AccountMargin()
{
    return qc->AccountMargin;
}

std::string MT4Bridge::QuoteClient::AccountName()
{
    return Util::convert(qc->AccountName);
}

double MT4Bridge::QuoteClient::AccountProfit()
{
    return qc->AccountProfit;
}

MT4Bridge::AccountType MT4Bridge::QuoteClient::AccountType()
{
    return MT4Bridge::AccountType(qc->AccountType);
}

bool MT4Bridge::QuoteClient::Connected()
{
    return qc->Connected;
}

DateTime MT4Bridge::QuoteClient::ConnectTime()
{
    return Util::convert(qc->ConnectTime);
}

std::string MT4Bridge::QuoteClient::Host()
{
    return Util::convert(qc->Host);
}

bool MT4Bridge::QuoteClient::IsInvestor()
{
    return qc->IsInvestor;
}

int MT4Bridge::QuoteClient::Port()
{
    return qc->Port;
}

std::vector<std::string> MT4Bridge::QuoteClient::Symbols()
{
    std::vector<std::string> ret;
    array<System::String^>^ arr = qc->Symbols;
    for (int i = 0; i < arr->Length; i++)
        ret.push_back(Util::convert(arr[i]));
    return ret;
}

void OnOnQuote(System::Object^ sender, TradingAPI::MT4Server::QuoteEventArgs^ args)
{
    EventArgs::quote_events.push_back({
        Util::convert(args->Symbol),
        args->Ask,
        args->Bid,
        Util::convert(args->Time)
    });
}

void QuoteClient::Subscribe(const std::string& symbol)
{
    qc->OnQuote += gcnew TradingAPI::MT4Server::QuoteEventHandler(&OnOnQuote);
    qc->Subscribe(Util::convert(symbol));
}

void MT4Bridge::QuoteClient::Unsubscribe(const std::string& symbol)
{
    qc->Unsubscribe(Util::convert(symbol));
}
