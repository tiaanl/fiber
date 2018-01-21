
#ifndef FIBER_CLIENT_SOCKET_H_
#define FIBER_CLIENT_SOCKET_H_

#include "fiber/Endpoint.h"
#include "fiber/Socket.h"

namespace fi {

class ClientSocket : public Socket {
public:
  virtual ~ClientSocket();

  virtual bool connect(const Endpoint& endpoint) = 0;
  virtual void disconnect() = 0;
  virtual bool isConnected() const = 0;
};

}  // namespace fi

#endif  // FIBER_CLIENT_SOCKET_H_
