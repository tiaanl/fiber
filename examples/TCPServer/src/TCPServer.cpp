
#include "fiber/ServerSocketTCP.h"
#include "fiber/Win/Winsock.h"
#include "nucleus/Containers/Array.h"
#include "nucleus/Logging.h"

int main() {
  fi::ScopedWinsockInitializer winsock;

  fi::ServerSocketTCP server;
  server.listen({fi::IpAddress::Localhost, 8080});

  nu::Array<U8, 1024> receiveBuffer;
  for (;;) {
    fi::Socket remote = server.accept();
    LOG(Info) << "New connection established";
    for (;;) {
      auto bytesReceived = remote.receive(receiveBuffer.getData(), receiveBuffer.getSize());
      if (bytesReceived == 0) {
        break;
      }
      LOG(Info) << "Bytes received: " << bytesReceived;
      receiveBuffer[bytesReceived] = 0;
      LOG(Info) << "Data: " << receiveBuffer.getData();
    }
    LOG(Info) << "Client disconnected.";
  }

  return 0;
}
