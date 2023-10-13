#include "BloodSocket.h"
#include "SocketUtil.h"
int BloodSocket::SetNonBlockingMode(bool inShouldBeNonBlocking)
{
	#if defined (_WIN32) || defined(__CYGWIN)// Windows x64 - x86
		u_long arg = inShouldBeNonBlocking ? 1 : 0;
		int result = ioctlsocket(mSocket, FIONBIO, &arg);
	#else
		int flags = fcntl(mSocket, F_GETFL, 0);
		flags = inShouldBeNonBlocking ?
			(flags | O_NONBLOCK) : (flags & ~O_NONBLOCK);
		fcntl(mSocket, F_SETFL, flags);
	#endif
		if (result == SOCKET_ERROR) {
			SocketUtil::ReportError(L"UDPSocket::SetNonBlockingMode");
			return SocketUtil::GetLastError();
		}
		else
			return NO_ERROR;
}
