
#include "fiber/IpAddress.h"

#include "nucleus/Win/WindowsMixin.h"

namespace fi {

// static
const IpAddress IpAddress::None{0, 0, 0, 0};
const IpAddress IpAddress::Localhost{127, 0, 0, 1};
const IpAddress IpAddress::Broadcast{255, 255, 255, 255};

IpAddress::IpAddress() noexcept : m_value(0) {}

IpAddress::IpAddress(U8 a, U8 b, U8 c, U8 d) noexcept {
  m_bytes[0] = a;
  m_bytes[1] = b;
  m_bytes[2] = c;
  m_bytes[3] = d;
}

IpAddress::IpAddress(U32 address) noexcept : m_value(address) {}

IpAddress::~IpAddress() = default;

void IpAddress::setValue(U32 value) {
  m_value = value;
}

nu::String IpAddress::toString() const {
  in_addr addr = {0, 0, 0, 0};
  addr.s_addr = m_value;
  const char* str = inet_ntoa(addr);
  return nu::String{str};
}

bool operator==(const IpAddress &left, const IpAddress &right) {
    return left.m_value == right.m_value;
}

}  // namespace fi
