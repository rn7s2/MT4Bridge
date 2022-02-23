#pragma once

#include <string>

#include "DLL.h"

// yyyy-MM-dd HH:mm:ss

namespace MT4Bridge
{
    class DLL_EXPORT DateTime
    {
    public:
        DateTime();
        DateTime(const std::string& datetime);
        int year();
        int month();
        int day();
        int hour();
        int minute();
        int second();
        std::string format();
        static DateTime Now();
        bool operator < (const DateTime& b) const;
        bool operator > (const DateTime& b) const;
        bool operator == (const DateTime& b) const;

    public:
#ifdef _MANAGED
        gcroot<System::DateTime^> datetime;
#else
        intptr_t datetime;
#endif
    };
}
