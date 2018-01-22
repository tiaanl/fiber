
#ifndef FIBER_SERVER_SOCKET_TCP_H_
#define FIBER_SERVER_SOCKET_TCP_H_

#include "fiber/Socket.h"
#include "fiber/Endpoint.h"

namespace fi {

class ServerSocketTCP : public Socket {
public:
  ServerSocketTCP();
  ~ServerSocketTCP() override;

  void listen(const Endpoint& endpoint);
  Socket accept();
};

}  // namespace fi

#endif  // FIBER_SERVER_SOCKET_TCP_H_
