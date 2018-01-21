
#include "catch.hpp"

#include "fiber/ClientSocketTCP.h"
#include "fiber/Resolver.h"
#include "fiber/Win/Winsock.h"
#include "nucleus/Containers/Array.h"
#include "nucleus/Logging.h"

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

TEST_CASE() {
  ScopedWinsockInitializer winsock;

  auto googleIP = resolve("www.google.com");
  auto google = Endpoint{googleIP, 80};

  ClientSocketTCP socket;
  if (socket.connect(google)) {
    const char buffer[] = "GET / HTTP/1.1\r\nHost: www.google.com\r\nConnection: close\r\n\r\n";
    socket.send(reinterpret_cast<const U8*>(buffer), std::strlen(buffer));

    nu::Array<U8, 1024> receiveBuf;
    for (;;) {
      I32 bytesReceived = socket.receive(receiveBuf.getData(), receiveBuf.getSize());
      LOG(Info) << "bytesReceived = " << bytesReceived;
      if (bytesReceived <= 0) {
        break;
      }

      receiveBuf[bytesReceived] = '\0';
      LOG(Info) << receiveBuf.getData();
    }
  }
}

}  // namespace fi
