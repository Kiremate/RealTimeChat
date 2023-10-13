#include "FDSetWrapper.h"
#include "BloodSocket.h"

FdSetWrapper::FdSetWrapper() {
    FD_ZERO(&fdSet);
}

void FdSetWrapper::AddSocket(const std::shared_ptr<BloodSocket>&socket) {
    FD_SET(socket->GetSocket(), &fdSet);
    sockets.push_back(socket);
}

bool FdSetWrapper::IsSocketActive(const std::shared_ptr<BloodSocket>& socket) const {
    return FD_ISSET(socket->GetSocket(), &fdSet);
}

fd_set* FdSetWrapper::GetRawFdSet() {
    return &fdSet;
}