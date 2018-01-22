
#include "fiber/ServerSocketTCP.h"
#include "fiber/Win/Winsock.h"
#include "nucleus/Containers/Array.h"
#include "nucleus/Logging.h"

int main() {
  fi::ScopedWinsockInitializer winsock;

  fi::ServerSocketTCP server;

  server.listen({fi::IpAddress::Localhost, 8080});

  const char* content =
      "<html><head><title>Test from C++</title></head><body><h1>Hello, World!</h1></body>";

  const char* buffer =
      "HTTP/1.1 200 OK\r\n"
      "Host: localhost\r\n"
      "Connection: close\r\n"
      "Content-length: %d\r\n"
      "Content-type: text/html\r\n"
      "\r\n";

  nu::Array<char, 1024> sendBuffer;
  std::sprintf(sendBuffer.getData(), "%s%s", buffer, content);
  std::sprintf(sendBuffer.getData(), sendBuffer.getData(), std::strlen(content));
  USize sendBufferLength = std::strlen(sendBuffer.getData());

  nu::Array<U8, 1024> receiveBuffer;
  for (;;) {
    fi::Socket newSocket = server.accept();

    // Read the request from the client.
    I32 bytesReceived = newSocket.receive(receiveBuffer.getData(), receiveBuffer.getSize());
    receiveBuffer[bytesReceived] = 0;
    LOG(Info) << receiveBuffer.getData();

    auto bytesSent = newSocket.send((const U8*)sendBuffer.getData(), sendBufferLength);
    LOG(Info) << "Bytes sent = " << bytesSent;
  }

  return 0;
}
