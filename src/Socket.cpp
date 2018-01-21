
#include "fiber/Socket.h"

#include "nucleus/Win/WindowsMixin.h"

namespace fi {

#if OS(WIN)
SocketHandle Socket::kInvalidSocketHandle = INVALID_SOCKET;
#elif OS(POSIX)
SocketHandle Socket::kInvalidSocketHandle = -1;
#else
#error "Could not determine type of sockets on this patform."
#endif

Socket::Socket() = default;

Socket::~Socket() = default;

}  // namespace fi
