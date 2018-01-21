
#include "catch.hpp"

#include "fiber/ClientSocketTCP.h"
#include "fiber/Resolver.h"
#include "fiber/Win/Winsock.h"

namespace fi {

TEST_CASE() {
  ScopedWinsockInitializer winsock;

  auto googleIP = resolve("www.google.com");
  auto google = Endpoint{googleIP, 80};

  ClientSocketTCP socket;
  socket.connect(google);
  CHECK(socket.isConnected());
  socket.disconnect();
  CHECK(!socket.isConnected());
}

}  // namespace fi
