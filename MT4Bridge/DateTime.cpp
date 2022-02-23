#include "pch.h"
#include "Util.h"
#include "DateTime.h"

using namespace TradingAPI;
using namespace MT4Bridge;

MT4Bridge::DateTime::DateTime()
{
    this->datetime = System::DateTime::MinValue;
}

DateTime::DateTime(const std::string& datetime)
{
    System::DateTime % res = System::DateTime();
    if (System::DateTime::TryParse(gcnew System::String(datetime.c_str()), res) != false)
        this->datetime = res;
    else
        this->datetime = System::DateTime::MinValue;
}

int DateTime::year()
{
    return datetime->Year;
}

int DateTime::month()
{
    return datetime->Month;
}

int DateTime::day()
{
    return datetime->Day;
}

int DateTime::hour()
{
    return datetime->Hour;
}

int DateTime::minute()
{
    return datetime->Minute;
}

int DateTime::second()
{
    return datetime->Second;
}

std::string DateTime::format()
{
    return Util::convert(datetime->ToString("yyyy-MM-dd HH:mm:ss"));
}

DateTime MT4Bridge::DateTime::Now()
{
    return Util::convert(System::DateTime::Now);
}

bool MT4Bridge::DateTime::operator<(const DateTime& b) const
{
    if (datetime->CompareTo(b.datetime) < 0)
        return true;
    return false;
}

bool MT4Bridge::DateTime::operator>(const DateTime& b) const
{
    if (datetime->CompareTo(b.datetime) > 0)
        return true;
    return false;
}

bool MT4Bridge::DateTime::operator==(const DateTime& b) const
{
    return datetime->Equals(b.datetime);
}
