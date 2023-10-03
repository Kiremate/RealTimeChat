# Real Time Chat in C++ using Berkeley Sockets 💬
## Overview 📖
This project aims to demonstrate the usage of Berkeley Sockets to create a real-time chat application.
The application is platform-agnostic, with support for Windows, Linux, and Unix-like systems. 
The project uses object-oriented programming and factory patterns to encapsulate socket functionality, making it easy to use and extend.

## Features ✨
- Cross-platform support (Windows, Linux, Unix-like)
- UDP and TCP protocols (UDP for future implementations)
- Scalable and extendable architecture
- Factory patterns for easy object creation

## Headers 📁
- PlatformErrorIncludes.h: Includes platform-specific headers for error handling.
- PlatformSocketIncludes.h: Includes platform-specific headers for socket programming.
- SocketAddress.h: Provides a class for handling IP addresses and ports.
- SocketAddressFactory.h: Factory class for creating SocketAddress objects.
- SocketFactory.h: Factory class for creating TCPSocket and UDPSocket objects.
- SocketUtil.h: Utility functions for reporting and handling errors.
- TCPSocket.h: Class that encapsulates TCP socket functionality.
- UDPSocket.h: Class that encapsulates UDP socket functionality.
## Source Files 📂
- main.cpp: The entry point for the application.
- TCPSocket.cpp: Implementation of TCPSocket class.
- UDPSocket.cpp: Implementation of UDPSocket class.

## Installation & Running 🚀
> [!NOTE]
> Still in development
### Windows 🪟
+ Visual Studio installed with C++ Support
+ Open the .sln build the project
### Linux / Unix 🐧
+ Open terminal and navigate to the project directory
+ Run 'make' to build the project.
+ Execute the output binary.

## Author 👤
Bloodmask

## License📜
License
This project is licensed under the MIT License.