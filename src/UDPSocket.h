#pragma once
#include "PlatformSocketIncludes.h"
#include <memory>
class SocketAddress;

class UDPSocket{
public:
	~UDPSocket();
	int Bind(const SocketAddress& inToAddress);
	int SendTo(const void* inData, int inLen, const SocketAddress& inTo);
	int ReceiveFrom(void* inBuffer, int inLen, SocketAddress& outFrom);
private:
	friend class SocketUtil;
	UDPSocket(SOCKET inSocket) : mSocket(inSocket){}
	SOCKET mSocket;
};
typedef std::shared_ptr<UDPSocket> UDPSocketPtr;