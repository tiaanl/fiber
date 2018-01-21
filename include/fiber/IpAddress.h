
#ifndef FIBER_IP_ADDRESS_H_
#define FIBER_IP_ADDRESS_H_

#include "nucleus/Text/String.h"

namespace fi {

class IpAddress {
public:
  // Static utility addresses.
  static const IpAddress None;
  static const IpAddress Localhost;
  static const IpAddress Broadcast;

  IpAddress() noexcept;

  // Construct the address from 4 bytes.
  IpAddress(U8 a, U8 b, U8 c, U8 d) noexcept;

  // Construct the address from a 32 bit integer value.
  explicit IpAddress(U32 address) noexcept;

  ~IpAddress();

  friend bool operator==(const IpAddress& left, const IpAddress& right);

  U32 getValue() const {
    return m_value;
  }
  void setValue(U32 value);

  // Return a string representation of the address in dotted format.
  nu::String toString() const;

private:
  union {
    // The ip address as a single 32-bit integer value.
    U32 m_value;

    // The ip address as a 4 part 8-bit value.
    U8 m_bytes[4];
  };
};

}  // namespace fi

#endif  // FIBER_IP_ADDRESS_H_
