#include "SocketLibraryInitializer.h"
#include "PlatformSocketIncludes.h"
#include "SocketUtil.h"

SocketLibraryInitializer::SocketLibraryInitializer()
{
	Initialize();
}

SocketLibraryInitializer::~SocketLibraryInitializer()
{
	Shutdown();
}

SocketLibraryInitializer::SocketLibraryInitializer(SocketLibraryInitializer&& lib) noexcept :
	m_initialized{ std::exchange(lib.m_initialized, false) }
#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
	, m_wsaData{ std::exchange(lib.m_wsaData, {}) }
#endif
{
}

SocketLibraryInitializer& SocketLibraryInitializer::operator=(SocketLibraryInitializer&& rhs) noexcept
{
	m_initialized = std::exchange(rhs.m_initialized, false);
#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
	m_wsaData = std::exchange(rhs.m_wsaData, {});
#endif
	return *this;
}

int SocketLibraryInitializer::Initialize()
{
#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
	int result = WSAStartup(MAKEWORD(2, 2), &m_wsaData);
	if (result != NO_ERROR)
	{
		SocketUtil::ReportError(L"SocketLibraryInitializer::Initialize");
		return SocketUtil::GetLastError();
	}
#endif
	m_initialized = true;
	return 0;
}

void SocketLibraryInitializer::Shutdown()
{
#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
	if (m_initialized)
	{
		std::ignore = WSACleanup();
	}
#endif
}