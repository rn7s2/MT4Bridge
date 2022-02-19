#include "pch.h"
#include "Server.h"

MT4Bridge::Server::Server(const std::string& host, const int port)
{
    this->host = host, this->port = port;
}
