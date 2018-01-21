
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

  virtual bool receive(U8* buffer, U32 bytesRead) = 0;
  virtual bool send(const U8* buffer, I32* bytesRead) = 0;

private:
  SocketHandle m_handle = kInvalidSocketHandle;
};

}  // namespace fi

#endif  // FIBER_SOCKET_H_
