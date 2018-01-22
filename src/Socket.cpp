
#include "fiber/Socket.h"

#include "nucleus/Logging.h"

#if OS(POSIX)
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#endif

namespace fi {

namespace {

#if defined(MSG_NOSIGNAL)
static const I32 kSendRecvFlags = MSG_NOSIGNAL;
#else
static const I32 kSendRecvFlags = 0;
#endif
}

#if OS(WIN)
SocketHandle Socket::kInvalidSocketHandle = INVALID_SOCKET;
#elif OS(POSIX)
SocketHandle Socket::kInvalidSocketHandle = -1;
#else
#error "Could not determine type of sockets on this patform."
#endif

Socket::Socket() = default;

Socket::Socket(SocketHandle socket) : m_handle(socket) {}

Socket::~Socket() = default;

I32 Socket::receive(U8* buffer, I32 bufferSize) {
  I32 bytesReceived = ::recv(m_handle, reinterpret_cast<char*>(buffer), bufferSize, kSendRecvFlags);
  if (bytesReceived >= 0) {
    return bytesReceived;
  }

  LOG(Error) << "Could not receive data on socket: " << bytesReceived;
  return 0;
}

I32 Socket::send(const U8* buffer, I32 bufferSize) {
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
