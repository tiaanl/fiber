
#ifndef FIBER_CLIENT_SOCKET_TCP_H_
#define FIBER_CLIENT_SOCKET_TCP_H_

#include "fiber/ClientSocket.h"

namespace fi {

class ClientSocketTCP : public ClientSocket {
public:
  ClientSocketTCP();
  ~ClientSocketTCP() override;

  bool connect(const Endpoint& endpoint) override;
  void disconnect() override;

  bool isConnected() const override {
    return m_isConnected;
  }

  I32 receive(U8 *buffer, I32 bufferSize) override;
  I32 send(const U8 *buffer, I32 bufferSize) override;

private:
  bool m_isConnected = false;
};

}  // namespace fi

#endif  // FIBER_CLIENT_SOCKET_TCP_H_
