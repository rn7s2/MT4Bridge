#include "pch.h"
#include "Bar.h"

MT4Bridge::Bar::Bar()
{}

MT4Bridge::Bar::Bar(
    const DateTime& datetime,
    double High,
    double Open,
    double Low,
    double Close,
    double Volume
)
{
    this->time = datetime, this->Volume = Volume;
    this->High = High, this->Open = Open;
    this->Low = Low, this->Close = Close;
}
