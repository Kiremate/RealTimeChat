#include "OutputMemoryStream.h"
#include <iostream>

void OutputMemoryStream::Write(const void* inData, size_t inByteCount)
{
	uint32_t resultHead = mHead + static_cast<uint32_t>(inByteCount);
	if (resultHead > mCapacity)
		ReallocBuffer(std::max(mCapacity * 2, resultHead));
	// copy into buffer at head
	std::memcpy(mBuffer + mHead, inData, inByteCount);
	// increment head for next write
	mHead = resultHead;
}

void OutputMemoryStream::ReallocBuffer(uint32_t inNewLength)
{
	auto newBuffer = static_cast<char*>(std::realloc(mBuffer, inNewLength));
	if (mBuffer == nullptr)
	{
		std::cerr << "Memory reallocation failed";
		throw std::bad_alloc();
	}
	else {
		mBuffer = newBuffer;
		mCapacity = inNewLength;
	}
}
