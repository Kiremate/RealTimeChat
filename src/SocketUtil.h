#pragma once
#include "PlatformErrorIncludes.h"

#include <memory>
#include <iostream>
#include <vector>

class BloodSocket;
class SocketUtil {

public:
	static void ReportError(const wchar_t* inOperationDesc);
	static int GetLastError();

	static fd_set* FillSetFromVector(fd_set& outSet, const std::vector<std::shared_ptr<BloodSocket>>* inSockets);
	static void FillVectorFromSet(
		std::vector<std::shared_ptr<BloodSocket>>* outSockets,
		const std::vector<std::shared_ptr<BloodSocket>>* inSockets, const fd_set& inSet);
	static int Select(
		const std::vector<std::shared_ptr<BloodSocket>>* inReadSet, std::vector<std::shared_ptr<BloodSocket>>* outReadSet,
		const std::vector<std::shared_ptr<BloodSocket>>* inWriteSet, std::vector<std::shared_ptr<BloodSocket>>* outWriteSet,
		const std::vector<std::shared_ptr<BloodSocket>>* inExceptSet, std::vector<std::shared_ptr<BloodSocket>>* outExceptSet);
	
private:

};
