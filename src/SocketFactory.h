#pragma once
#include <memory>
#include "UDPSocket.h"
#include "SocketUtil.h"

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
};
