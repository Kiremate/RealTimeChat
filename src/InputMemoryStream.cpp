#include "InputMemoryStream.h"
#include <stdexcept>

void InputMemoryStream::Read(void* outData, uint32_t inByteCount)
{
	if ((mHead + inByteCount) > mCapacity)
		throw std::runtime_error("Not enough bytes left in stream to perform read operation");
	
	memcpy(outData, mBuffer + mHead, inByteCount);
	mHead += inByteCount;
}
void InputMemoryStream::ResetToZero() {
	mHead = 0;
}
