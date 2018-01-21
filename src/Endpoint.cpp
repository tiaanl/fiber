
#include "fiber/Endpoint.h"

namespace fi {

// static bool resolve(const nu::String& host, U16 port, Endpoint* endpointOut);

Endpoint::Endpoint() = default;

Endpoint::Endpoint(const IpAddress& ipAddress, U16 port) : m_ipAddress(ipAddress), m_port(port) {}

void Endpoint::setIpAddress(const IpAddress& ipAddress) {
  m_ipAddress = ipAddress;
}

void Endpoint::setPort(U16 port) {
  m_port = port;
}

}  // namespace fi
