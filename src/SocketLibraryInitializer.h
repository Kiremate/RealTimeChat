#pragma once

#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
#include <WinSock2.h>
#endif

#include <utility> 

class SocketLibraryInitializer final {
private:
    bool m_initialized{ false };
#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
    WSADATA m_wsaData{};
#endif
public:
    SocketLibraryInitializer();
    ~SocketLibraryInitializer();
    SocketLibraryInitializer(const SocketLibraryInitializer&) = delete;
    SocketLibraryInitializer& operator=(const SocketLibraryInitializer&) = delete;
    SocketLibraryInitializer(SocketLibraryInitializer&& lib) noexcept;
    SocketLibraryInitializer& operator=(SocketLibraryInitializer&& rhs) noexcept;

    int Initialize();
    void Shutdown();
    bool IsInitialized() const { return m_initialized; }
    explicit operator bool() const { return m_initialized; }
#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
    const WSADATA& GetWSAData() const { return m_wsaData; }
#endif
};