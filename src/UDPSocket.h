#pragma once
#include "BloodSocket.h"
#include <memory>
class SocketAddress;

class UDPSocket : public BloodSocket{
public:
	~UDPSocket();
	int Bind(const SocketAddress& inToAddress) override;
	int SendTo(const void* inData, int inLen, const SocketAddress& inTo);
	int ReceiveFrom(void* inBuffer, int inLen, SocketAddress& outFrom);
	int SetNonBlockingMode(bool inShouldBeNonBlocking) override;
private:
	friend class SocketUtil;
	UDPSocket(SOCKET inSocket) : BloodSocket(inSocket){}
};
typedef std::shared_ptr<UDPSocket> UDPSocketPtr;