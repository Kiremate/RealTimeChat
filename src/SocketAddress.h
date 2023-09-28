#pragma once
#include "PlatformSocketIncludes.h"
#include <cstdint>
class SocketAddress {
public:
	SocketAddress(uint32_t inAddress, uint16_t inPort) {
		
	}

private:
	sockaddr mSockAddr;
};
