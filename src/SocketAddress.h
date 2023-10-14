#pragma once
#include "PlatformSocketIncludes.h"
#include <cstdint>
#include <cstring>
#include <memory>

enum SocketAddressFamily {
	INET = AF_INET,
	INET6 = AF_INET6
};

class SocketAddress {
public:
	SocketAddress(uint32_t inAddress, uint16_t inPort) { // IPV4 Constructor
		GetAsSockAddrIn()->sin_family = AF_INET;
	#if defined(_WIN32) || defined(__CYGWIN)
		GetAsSockAddrIn()->sin_addr.S_un.S_addr = htonl(inAddress);
	#else
		GetAsSockAddrIn()->sin_addr.s_addr = htonl(inAddress);
	#endif
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

	size_t GetSize() const { return sizeof(sockaddr); }

private:
	friend class UDPSocket;
	friend class TCPSocket;
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