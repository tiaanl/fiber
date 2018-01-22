
#include "fiber/ServerSocketTCP.h"

#include "nucleus/Logging.h"

namespace fi {


ServerSocketTCP::ServerSocketTCP() = default;

ServerSocketTCP::~ServerSocketTCP() = default;

void ServerSocketTCP::listen(const Endpoint &endpoint) {
  // Create the socket.
  m_handle = ::socket(PF_INET, SOCK_STREAM, 0);

  // Make sure the address is valid.
  if (endpoint.getIpAddress() == IpAddress::None || endpoint.getIpAddress() == IpAddress::Broadcast) {
    LOG(Fatal) << "Connot listen on 0.0.0.0 or 255.255.255.255 addressed.";
    return;
  }

  // Bind the socket to the specified port.
  sockaddr_in addr;
  std::memset(&addr, 0, sizeof(addr));
  addr.sin_addr.s_addr = endpoint.getIpAddress().getValue();
  addr.sin_family = AF_INET;
  addr.sin_port = htons(endpoint.getPort());

  if (::bind(m_handle, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == -1) {
    LOG(Error) << "Could not bind to port " << endpoint.getPort() << ".";
    return;
  }

  if (::listen(m_handle, 0) == -1) {
    LOG(Error) << "Could not listen on port " << endpoint.getPort();
    return;
  }
}

Socket ServerSocketTCP::accept() {
  // Make sure that we're listening.
  if (m_handle == kInvalidSocketHandle) {
    LOG(Error) << "Can not accept a connection on a non listening port.";
    return {};
  }

  // Accept a new connection.
  sockaddr_in addr;
  I32 size = sizeof(addr);
  SocketHandle remote = ::accept(m_handle, reinterpret_cast<sockaddr*>(&addr), &size);
  if (remote == kInvalidSocketHandle) {
    LOG(Error) << "Could not accept new connection.";
    return {};
  }

  return Socket{remote};
}

}  // namespace fi
