
#include "fiber/Win/Winsock.h"
#include "nucleus/Logging.h"

namespace fi {


ScopedWinsockInitializer::ScopedWinsockInitializer() {
  int result = ::WSAStartup(MAKEWORD(2, 2), &m_wsaData);
  if (result != 0) {
    LOG(Fatal) << "WSAStartup failed: " << result;
  }
}

ScopedWinsockInitializer::~ScopedWinsockInitializer() {
  int result = ::WSACleanup();
  if (result != 0) {
    LOG(Fatal) << "WSACleanup failed: " << result;
  }
}

}  // namespace fi
