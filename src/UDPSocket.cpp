#include "UDPSocket.h"
#include "SocketUtil.h"
#include "SocketAddress.h"
int UDPSocket::Bind(const SocketAddress& inBindAddress)
{
	auto error = bind(mSocket, &inBindAddress.mSockAddr, inBindAddress.GetSize());
	if (error != 0)
	{
		SocketUtil::ReportError(L"UDPSocket::Bind");
		return -SocketUtil::GetLastError();
	}
	return NO_ERROR;
}

int UDPSocket::SendTo(const void* inData, int inLen, const SocketAddress& inTo)
{
	int byteSentCount = sendto(mSocket, static_cast<const char*>(inData), static_cast<int>(inLen), 0, &inTo.mSockAddr,
		static_cast<int>(inTo.GetSize()));
	if (byteSentCount >= 0)
		return byteSentCount;
	else
	{
		SocketUtil::ReportError(L"UDPSocket::SendTo");
		return -SocketUtil::GetLastError();
	}
}

int UDPSocket::ReceiveFrom(void* inBuffer, int inLen, SocketAddress& outFrom)
{
	int fromLength = outFrom.GetSize();
	int readyByteCount = recvfrom(mSocket, static_cast<char*>(inBuffer), inLen, 0, &outFrom.mSockAddr, &fromLength);
	if (readyByteCount >= 0)
		return readyByteCount;
	else {
		SocketUtil::ReportError(L"UDPSocket::ReceiveFrom");
		return -SocketUtil::GetLastError();
	}
}

UDPSocket::~UDPSocket()
{
	closesocket(mSocket);
}
