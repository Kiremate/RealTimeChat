#pragma once
#if defined(_WIN32) || defined(__CYGWIN)// Windows x64 - x86
	#define WIN32_LEAN_AND_MEAN  // Exclude rarely-used stuff from Windows headers
	#include <WinSock2.h>
	#include <WS2tcpip.h>
	#include <Windows.h>
#elif defined(__linux__) // Linux
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <netdb.h>
	#include <fcntl.h>  
	typedef int SOCKET;
	#define INVALID_SOCKET -1
	#define SOCKET_ERROR -1
#elif defined(unix) || defined(__unix__) || defined(__unix) // Unix like OS like PS4/5
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <netdb.h>
#endif
