
#include "catch.hpp"

#include "fiber/Resolver.h"
#include "fiber/Win/Winsock.h"

namespace fi {

TEST_CASE() {
  ScopedWinsockInitializer winsock;

  auto result2 = resolve("localhost");
  REQUIRE(result2 == IpAddress::Localhost);
}

}  // namespace fi
