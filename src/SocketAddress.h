#pragma once
#include "PlatformSocketIncludes.h"
#include <cstdint>
#include <memory>
class SocketAddress {
public:
	SocketAddress(uint32_t inAddress, uint16_t inPort) { // IPV4 Constructor
		GetAsSockAddrIn()->sin_family = AF_INET;
		GetAsSockAddrIn()->sin_addr.S_un.S_addr = htonl(inAddress);
		GetAsSockAddrIn()->sin_port = htons(inPort);
	}
	SocketAddress(const uint8_t inAddress[16], uint16_t inPort) { // IPV6 Constructor
		GetAsSockAddrIn6()->sin6_family = AF_INET6;
		memcpy(&GetAsSockAddrIn6()->sin6_addr, inAddress, 16);
		GetAsSockAddrIn6()->sin6_port = htons(inPort);
	}
	SocketAddress(const sockaddr& inSockAddr) { // Copy Constructor
		memcpy(&mSockAddr, &inSockAddr, sizeof(inSockAddr));
	}

private:
	union {
		sockaddr mSockAddr;
		sockaddr_in mSockAddr4;
		sockaddr_in6 mSockAddr6;
	};
	
	sockaddr_in* GetAsSockAddrIn() {
		return &mSockAddr4;
	}
	sockaddr_in6* GetAsSockAddrIn6() {
		return &mSockAddr6;
	}
};

typedef std::shared_ptr<SocketAddress> SocketAddressPtr;