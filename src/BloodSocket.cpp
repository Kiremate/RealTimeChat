#include "BloodSocket.h"
#include "SocketUtil.h"

BloodSocket::~BloodSocket() {
    #if defined(_WIN32) || defined(__CYGWIN)
        closesocket(mSocket);
    #else
        close(mSocket);
    #endif
}

int BloodSocket::SetNonBlockingMode(bool inShouldBeNonBlocking)
{
    int result = 0;  // Initialize result to a neutral value

    #if defined(_WIN32) || defined(__CYGWIN) // Windows x64 - x86
        u_long arg = inShouldBeNonBlocking ? 1 : 0;
        result = ioctlsocket(mSocket, FIONBIO, &arg);
    #else // Linux/Unix
        int flags = fcntl(mSocket, F_GETFL, 0);
        flags = inShouldBeNonBlocking ? (flags | O_NONBLOCK) : (flags & ~O_NONBLOCK);
        result = fcntl(mSocket, F_SETFL, flags);

    // If fcntl failed, set result to SOCKET_ERROR
    if (result == -1) {
        result = SOCKET_ERROR;
    }
    #endif

    // Check for any errors
    if (result == SOCKET_ERROR) {
        SocketUtil::ReportError(L"BloodSocket::SetNonBlockingMode");
        return SocketUtil::GetLastError();
    }
    else {
        // No errors, so return NO_ERROR or its equivalent
    #if defined(_WIN32) || defined(__CYGWIN)
        return NO_ERROR;
    #else
        return 0;  // Equivalent of NO_ERROR in Linux/Unix
    #endif
    }
}
