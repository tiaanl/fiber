
#ifndef FIBER_WIN_WINSOCK_H_
#define FIBER_WIN_WINSOCK_H_

#include "nucleus/Macros.h"
#include "nucleus/Win/WindowsMixin.h"

namespace fi {

class ScopedWinsockInitializer {
public:
  COPY_DELETE(ScopedWinsockInitializer);
  MOVE_DELETE(ScopedWinsockInitializer);

  ScopedWinsockInitializer();
  ~ScopedWinsockInitializer();

private:
  WSADATA m_wsaData;
};

}  // namespace fi

#endif  // FIBER_WIN_WINSOCK_H_
