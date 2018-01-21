
#ifndef FIBER_SOCKET_H_
#define FIBER_SOCKET_H_

#include "fiber/SocketHandle.h"
#include "nucleus/Types.h"

namespace fi {

class Socket {
public:
  static SocketHandle kInvalidSocketHandle;

  Socket();
  virtual ~Socket();

  virtual I32 receive(U8* buffer, I32 bufferSize) = 0;
  virtual I32 send(const U8* buffer, I32 bufferSize) = 0;

protected:
  SocketHandle m_handle = kInvalidSocketHandle;
};

}  // namespace fi

#endif  // FIBER_SOCKET_H_
