#pragma once
// Include platform-specific headers for error handling
#if defined (_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
#include <WinSock2.h> // for WSAGetLastError
#elif defined(__linux__)
#include <errno.h>    // for errno
#elif defined(unix) || defined(__unix__) || defined(__unix)
#include <errno.h>    // for errno
#endif