#pragma once

#include <string>

#include "DLL.h"

namespace MT4Bridge
{
    class DLL_EXPORT Server
    {
    public:
        Server(const std::string& host, const int port);

    public:
        std::string host;
        int port;
    };
}
