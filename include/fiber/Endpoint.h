
#ifndef FIBER_ENDPOINT_H_
#define FIBER_ENDPOINT_H_

#include "nucleus/Text/String.h"
#include "fiber/IpAddress.h"

namespace fi {

class Endpoint {
public:
  Endpoint();
  Endpoint(const IpAddress& ipAddress, U16 port);

  const IpAddress& getIpAddress() const {
    return m_ipAddress;
  }
  void setIpAddress(const IpAddress& ipAddress);

  U16 getPort() const {
    return m_port;
  }
  void setPort(U16);

private:
  IpAddress m_ipAddress;
  U16 m_port = 0;
};

}  // namespace fi

#endif  // FIBER_ENDPOINT_H_
