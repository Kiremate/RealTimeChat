#include "SocketUtil.h"
#include "BloodSocket.h"
#include <iostream>


void SocketUtil::ReportError(const wchar_t* inOperationDesc) {
	std::wcerr << L"Error: " << inOperationDesc << L" - " << GetLastError() << std::endl;
}
int SocketUtil::GetLastError() {
	#if defined (_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
		return WSAGetLastError();  // Windows-specific
	#elif defined(__linux__)
		return errno;  // Linux-specific, include <errno.h>
	#elif defined(unix) || defined(__unix__) || defined(__unix)
		return errno;  // Unix-specific, include <errno.h>
		// Unknown platform
		return -1;
	#endif
}

fd_set* SocketUtil::FillSetFromVector(fd_set& outSet, const std::vector<std::shared_ptr<BloodSocket>>* inSockets) {
	if (inSockets) {
		FD_ZERO(&outSet);
		for (const auto& socket : *inSockets) {
			FD_SET(socket->GetSocket(), &outSet);
		}
		return &outSet;
	}
	else {
		return nullptr;
	}
}
void SocketUtil::FillVectorFromSet(std::vector<std::shared_ptr<BloodSocket>>* outSockets, const std::vector<std::shared_ptr<BloodSocket>>* inSockets, const fd_set& inSet) {
	if (inSockets && outSockets) {
		outSockets->clear();
		for (const auto& socket : *inSockets) {
			if (FD_ISSET(socket->GetSocket(), &inSet)) {
				outSockets->push_back(socket);
			}
		}
	}
}
int SocketUtil::Select(const std::vector<std::shared_ptr<BloodSocket>>* inReadSet, std::vector<std::shared_ptr<BloodSocket>>* outReadSet,
	const std::vector<std::shared_ptr<BloodSocket>>* inWriteSet, std::vector<std::shared_ptr<BloodSocket>>* outWriteSet,
	const std::vector<std::shared_ptr<BloodSocket>>* inExceptSet, std::vector<std::shared_ptr<BloodSocket>>* outExceptSet) {
	fd_set read, write, except;
	fd_set* readPtr = FillSetFromVector(read, inReadSet);
	fd_set* writePtr = FillSetFromVector(write, inWriteSet);
	fd_set* exceptPtr = FillSetFromVector(except, inExceptSet);

	int toRet = select(0, readPtr, writePtr, exceptPtr, nullptr);
	if (toRet > 0) {
		FillVectorFromSet(outReadSet, inReadSet, read);
		FillVectorFromSet(outWriteSet, inWriteSet, write);
		FillVectorFromSet(outExceptSet, inExceptSet, except);
	}

	return toRet;
}