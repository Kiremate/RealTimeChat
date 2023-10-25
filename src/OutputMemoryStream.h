#pragma once
#include <cstdint> 
#include <cstdlib> 
#include <memory>
#include <type_traits>
class OutputMemoryStream{

public:

	OutputMemoryStream() :
		mBuffer(nullptr), mHead(0), mCapacity(0) {
		ReallocBuffer(32);
	}
	~OutputMemoryStream() { std::free(mBuffer); }

	// get a pointer to the data in the stream
	const char* GetBufferPtr() const { return mBuffer; }
	uint32_t GetLength() const { return mHead; }

	void Write(const void* inData, size_t inByteCount);
	void Write(uint32_t inData) { Write(&inData, sizeof(inData)); }
	void Write(int32_t inData) { Write(&inData, sizeof(inData)); }

	template<typename T>
	void Write(T inData) {
		static_assert(std::is_arithmetic<T>::value ||
			std::is_enum<T>::value,
			"Generic Write only supports primitive data types");
		Write(&inData, sizeof(inData));
	}
private:
	void ReallocBuffer(uint32_t inNewLength);
	char* mBuffer;
	uint32_t mHead;
	uint32_t mCapacity;
};
