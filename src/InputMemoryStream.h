#pragma once
#include <cstdint> 
#include <cstdlib> 
#include <cstring> 
class InputMemoryStream{

public:
	InputMemoryStream(char* inBuffer, uint32_t inByteCount, bool ownsBuffer = false): 
		mBuffer(inBuffer), mCapacity(inByteCount), mHead(0), mOwnsBuffer(ownsBuffer) {}
	~InputMemoryStream() {
		if(mOwnsBuffer)
			std::free(mBuffer);
	}
	uint32_t GetRemainingDataSize() const { return mCapacity - mHead; }
	void Read(void* outData, uint32_t inByteCount);
	void Read(uint32_t& outData) { Read(&outData, sizeof(outData)); }
	void Read(int32_t& outData) { Read(&outData, sizeof(outData)); }
private:
	bool mOwnsBuffer;
	void ResetToZero();
	char* mBuffer;
	uint32_t mHead;
	uint32_t mCapacity;
};
