#pragma once
#include "SocketAddress.h"
#include <string>
#include <stdexcept>
class SocketAddressFactory {

public:
	static SocketAddressPtr CreateIPv4FromString(const std::string& inString) {
		auto pos = inString.find_last_of(':'); // So we can separate ip from port
		std::string host, service;
		if (pos != std::string::npos) {
			host = inString.substr(0, pos); // IP
			service = inString.substr(pos + 1); // port
		}
		else {
			host = inString;
			service = "0"; // Default Port
		}
		addrinfo hint; 
		memset(&hint, 0, sizeof(hint));
		hint.ai_family = AF_INET;
		
		addrinfo* result; 
		// GedAddrInfo possible bottleneck, separate it in another thread
		int error = getaddrinfo(host.c_str(), service.c_str(), &hint, &result);
		if (error != 0 && result != nullptr)
		{
			freeaddrinfo(result);
			return nullptr;
		}
		while (!result->ai_addr && result->ai_next) {
			result = result->ai_next;
		}
		if (!result->ai_addr) {
			freeaddrinfo(result);
			return nullptr;
		}
		auto toRet = std::make_shared<SocketAddress>(*result->ai_addr);
		freeaddrinfo(result);
		return toRet;
	}
	static SocketAddressPtr CreateIPv6FromString(const std::string& inString) {
		auto lastBracketPos = inString.find_last_of(']'); // [2a0c:5a81:a102:b700:69d0:ac76:adcf:f9dc]:8080
		auto lastColonPos = inString.find_last_of(':');
		std::string host, service;
	
		if (lastBracketPos > lastColonPos) { // This means the host is larger than the service then the format is
											// this one [2a0c:5a81:a102:b700:69d0:ac76:adcf:f9dc]:8080
			host = inString.substr(1, lastBracketPos - 1);
			service = inString.substr(lastBracketPos + 1);
		}
		else {
			throw std::runtime_error("Malformed IPv6 string");
		}
		addrinfo hint;
		memset(&hint, 0, sizeof(hint));
		hint.ai_family = AF_INET6;
		addrinfo* result;
		// GedAddrInfo possible bottleneck, separate it in another thread
		int error = getaddrinfo(host.c_str(), service.c_str(), &hint, &result);
		if (error != 0) {
			if (result) {
				freeaddrinfo(result);
			}
			return nullptr;
		}
		while (!result->ai_addr && result->ai_next) 
			result = result->ai_next;
		
		if (!result->ai_addr) {
			freeaddrinfo(result);
			return nullptr;
		}
		auto toRet = std::make_shared<SocketAddress>(*result->ai_addr);
		freeaddrinfo(result);
		return toRet;
	}
private:

};
