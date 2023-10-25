#pragma once
#include <cstdint>
#include <memory>
class OutputMemoryBitStream {

public:
	OutputMemoryBitStream() { ReallocBuffer(256); }
	~OutputMemoryBitStream() { std::free(mBuffer); }
	void WriteBits(uint8_t inDdata, size_t inBitCount);
	void WriteBits(const void* inData, size_t inBitCount);
	const char* GetBufferPtr() const { return mBuffer; }
	uint32_t GetBitLength() const { return mBitHead; }
	uint32_t GetByteLength() const { return (mBitHead + 7) >> 3; }
	void WriteBytes(const void* inData, size_t inByteCount) { WriteBits(inData, inByteCount << 3); }
private:
	void ReallocBuffer(uint32_t inNewBitCapacity);
	char* mBuffer;
	uint32_t mBitHead;
	uint32_t mBitCapacity;

};
