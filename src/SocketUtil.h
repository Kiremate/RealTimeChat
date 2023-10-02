#pragma once
#include <iostream>
#include "PlatformErrorIncludes.h"


class SocketUtil {

public:
	static void ReportError(const wchar_t* inOperationDesc) {
		std::wcerr << L"Error: " << inOperationDesc << L" - " << GetLastError() << std::endl;
	}
	static int GetLastError() {
	#if defined (_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
			return WSAGetLastError();  // Windows-specific
	#elif defined(__linux__)
			return errno;  // Linux-specific, include <errno.h>
	#elif defined(unix) || defined(__unix__) || defined(__unix)
			return errno;  // Unix-specific, include <errno.h>
	#else
			// Unknown platform
			return -1;
	#endif
	}

private:

};
