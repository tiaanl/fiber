
#include "fiber/ClientSocketTCP.h"

#include "nucleus/Logging.h"

namespace fi {

namespace {

#if defined(MSG_NOSIGNAL)
static const I32 kSendRecvFlags = MSG_NOSIGNAL;
#else
static const I32 kSendRecvFlags = 0;
#endif
}

ClientSocketTCP::ClientSocketTCP() = default;

ClientSocketTCP::~ClientSocketTCP() {
  disconnect();
}

bool ClientSocketTCP::connect(const Endpoint& endpoint) {
  m_handle = ::socket(AF_INET, SOCK_STREAM, 0);
  if (m_handle == kInvalidSocketHandle) {
    LOG(Error) << "Could not create socket.";
    return false;
  }

  // Create the address structure that we're going to use to connect.
  sockaddr_in addr;
  std::memset(&addr, 0, sizeof(addr));
  addr.sin_addr.s_addr = endpoint.getIpAddress().getValue();
  addr.sin_family = AF_INET;
  addr.sin_port = htons(endpoint.getPort());

  // Connect the socket to the remote address.
  if (::connect(m_handle, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == -1) {
    LOG(Error) << "Could not connect to: " << endpoint;
    return false;
  }

  m_isConnected = true;

  return true;
}

void ClientSocketTCP::disconnect() {
  if (m_handle != kInvalidSocketHandle) {
#if OS(WIN)
    ::closesocket(m_handle);
#elif OS(POSIX)
    ::close(m_handle);
#else
#error "Don't know how to close this socket"
#endif
  }

  m_isConnected = false;
}

I32 ClientSocketTCP::receive(U8* buffer, I32 bufferSize) {
  I32 bytesReceived = ::recv(m_handle, reinterpret_cast<char*>(buffer), bufferSize, kSendRecvFlags);
  if (bytesReceived >= 0) {
    return bytesReceived;
  }

  LOG(Error) << "Could not receive data on socket: " << bytesReceived;
  return 0;
}

I32 ClientSocketTCP::send(const U8* buffer, I32 bufferSize) {
  // Loop until every byte was sent.
  I32 totalBytesSent = 0;

  for (;;) {
    I32 bytesSent = ::send(m_handle, reinterpret_cast<const char*>(buffer), bufferSize, kSendRecvFlags);
    if (bytesSent < 0) {
      LOG(Error) << "Could not send data on socket: " << bytesSent;
      return 0;
    }

    if (bytesSent == 0) {
      LOG(Warning) << "Socket closed.";
      return 0;
    }

    totalBytesSent += bytesSent;

    if (totalBytesSent >= bufferSize) {
      break;
    }
  }

  return totalBytesSent;
}

}  // namespace fi
