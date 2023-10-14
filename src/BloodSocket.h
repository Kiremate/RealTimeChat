#pragma once
#include "PlatformErrorIncludes.h"
#include "PlatformSocketIncludes.h"
class SocketAddress;

class BloodSocket{
public:
    virtual ~BloodSocket() = default;
    virtual int Bind(const SocketAddress& inToAddress) = 0;
    virtual int SetNonBlockingMode(bool inShouldBeNonBlocking) = 0;
    SOCKET GetSocket() const { return mSocket; }

protected:
    BloodSocket(SOCKET inSocket) : mSocket(inSocket) {}
    SOCKET mSocket;
};
