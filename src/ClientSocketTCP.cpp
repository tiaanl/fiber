
#include "fiber/ClientSocketTCP.h"

#include "nucleus/Logging.h"

#if OS(POSIX)
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

namespace fi {

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

}  // namespace fi
