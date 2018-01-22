
#include <thread>
#include <chrono>

#include "fiber/ClientSocketTCP.h"
#include "fiber/Win/Winsock.h"
#include "nucleus/Logging.h"

int main() {
  using namespace std::chrono_literals;

  fi::ScopedWinsockInitializer winsock;

  fi::ClientSocketTCP socket;
  if (socket.connect({fi::IpAddress::Localhost, 8080})) {
    for (int i = 0; i < 10; ++i) {
      auto bytesSent = socket.send((const U8*)"hello", 6);
      LOG(Info) << "Bytes sent: " << bytesSent;
#if OS(WIN)
      ::Sleep(200);
#elif OS(POSIX)
      std::this_thread::sleep_for(2s);
#endif
    }
  }

  return 0;
}
