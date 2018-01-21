
#include "catch.hpp"
#include "fiber/IpAddress.h"

namespace fi {

TEST_CASE() {
  IpAddress addr1;

  REQUIRE(addr1.getValue() == 0);
}

TEST_CASE() {
  IpAddress addr1{192, 168, 10, 1};

  CHECK(addr1.getValue() == 17475776);
}

TEST_CASE() {
  IpAddress addr1{192, 168, 0, 1};
  IpAddress addr2{1, 1, 1, 1};
  IpAddress addr3{254, 254, 254, 254};

  CHECK(addr1.toString() == "192.168.0.1");
  CHECK(addr2.toString() == "1.1.1.1");
  CHECK(addr3.toString() == "254.254.254.254");
}

TEST_CASE() {
    IpAddress addr = IpAddress::Localhost;
    CHECK(addr.toString() == "127.0.0.1");
    addr.setValue(10);
    CHECK(addr.getValue() == 10);
}

}  // namespace fi
