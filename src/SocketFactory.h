#pragma once
#include <memory>
#include "UDPSocket.h"
#include "TCPSocket.h"
#include "SocketUtil.h"


enum SocketAddressFamily;

class SocketFactory {
public:
    static std::shared_ptr<UDPSocket> CreateUDPSocket(SocketAddressFamily inFamily) {
        SOCKET s = socket(inFamily, SOCK_DGRAM, IPPROTO_UDP);
        if (s != INVALID_SOCKET) {
            return std::make_shared<UDPSocket>(s);
        }
        else {
            SocketUtil::ReportError(L"SocketFactory::CreateUDPSocket");
            return nullptr;
        }
    }
    static std::shared_ptr<TCPSocket> CreateTCPSocket(SocketAddressFamily inFamily) {
        SOCKET s = socket(inFamily, SOCK_STREAM, IPPROTO_TCP);
        if (s != INVALID_SOCKET)
            return std::make_shared<TCPSocket>(s);
        else {
            SocketUtil::ReportError(L"SocketFactory::CreateTCPSocket");
            return nullptr;
        }
    }
};
