#pragma once
#include "BloodSocket.h"
#include <memory>
class SocketAddress;

class TCPSocket : public BloodSocket{
public:
	~TCPSocket() override;
	int Connect(const SocketAddress& inAddress);
	int Bind(const SocketAddress& inToAddress) override;
	int Listen(int inBackLog = 32);
	std::shared_ptr<TCPSocket> Accept(SocketAddress& inFromAddress);
	int Send(const void* inDdata, int inLen);
	int Receive(void* inBuffer, int inLen);
	int SetNonBlockingMode(bool inShouldBeNonBlocking) override;
private:
	friend class SocketUtil;
	TCPSocket(SOCKET inSocket) : BloodSocket(inSocket){}
};
typedef std::shared_ptr<TCPSocket> TCPSocketPtr;
