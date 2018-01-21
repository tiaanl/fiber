
#ifndef FIBER_SOCKET_HANDLE_H_
#define FIBER_SOCKET_HANDLE_H_

#include "nucleus/Config.h"
#include "nucleus/Win/WindowsMixin.h"

namespace fi {

#if OS(WIN)
using SocketHandle = UINT_PTR;
#elif OS(POSIX)
using SocketHandle = I32;
#else
#error "Could not determine type of sockets on this patform."
#endif

}  // namespace fi

#endif  // FIBER_SOCKET_HANDLE_H_
