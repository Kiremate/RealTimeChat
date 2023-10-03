#include "TCPSocket.h"
#include "SocketUtil.h"
#include "SocketAddress.h"
TCPSocket::~TCPSocket()
{
	closesocket(mSocket);
}

int TCPSocket::Connect(const SocketAddress& inAddress)
{
	int error = connect(mSocket, &inAddress.mSockAddr, inAddress.GetSize());
	if (error < 0) {
		SocketUtil::ReportError(L"TCPSocket::Connect");
		return -SocketUtil::GetLastError();
	}
}

int TCPSocket::Bind(const SocketAddress& inToAddress)
{
	int error = bind(mSocket, &inToAddress.mSockAddr, inToAddress.GetSize());
	if (error != 0) {
		SocketUtil::ReportError(L"TCPSocket::Bind");
		return -SocketUtil::GetLastError();
	}
	return NO_ERROR;
}

int TCPSocket::Listen(int inBackLog)
{
	int error = listen(mSocket, inBackLog);
	if (error < 0) {
		SocketUtil::ReportError(L"TCPSocket::Listen");
		return -SocketUtil::GetLastError();
	}
	return NO_ERROR;
}

std::shared_ptr<TCPSocket> TCPSocket::Accept(SocketAddress& inFromAddress)
{
	int length = inFromAddress.GetSize();
	SOCKET newSocket = accept(mSocket, &inFromAddress.mSockAddr, &length);
	if (newSocket != INVALID_SOCKET) {
		return TCPSocketPtr(new TCPSocket(newSocket));
	}
	else {
		SocketUtil::ReportError(L"TCPSocket::Accept");
		return nullptr;
	}
}

int TCPSocket::Send(const void* inData, int inLen)
{
	int bytesSentCount = send(mSocket, static_cast<const char*>(inData),
		inLen, 0);
	if (bytesSentCount < 0) {
		SocketUtil::ReportError(L"TCPSocket::Send");
		return -SocketUtil::GetLastError();
	}
	return bytesSentCount;
}

int TCPSocket::Receive(void* inBuffer, int inLen)
{
	int bytesReceivedCount = recv(mSocket, static_cast<char*>(inBuffer), inLen, 0);
	if (bytesReceivedCount < 0) {
		SocketUtil::ReportError(L"TCPSocket::Receive");
		return -SocketUtil::GetLastError();
	}
	return bytesReceivedCount;
}
