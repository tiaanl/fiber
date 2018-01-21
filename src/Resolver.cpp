
#include "fiber/Resolver.h"

#include "nucleus/Logging.h"
#include "nucleus/Win/WindowsMixin.h"

namespace fi {

IpAddress resolve(const nu::String& host) noexcept {
  hostent* remoteHost;

  remoteHost = gethostbyname(host.getRawBytes());
  if (!remoteHost) {
    DWORD errorCode = WSAGetLastError();
    switch (errorCode) {
      case WSAHOST_NOT_FOUND:
        LOG(Warning) << "resolve: Host not found: " << host;
        return {};

      case WSANO_DATA:
        LOG(Warning) << "resolve: No data record: " << host;
        return {};

      default:
        LOG(Warning) << "resolve: Failed with error: " << errorCode;
        return {};
    }
  }

  LOG(Info) << "resolve returned:";

  LOG(Info) << "  Official name: " << remoteHost->h_name;
  I32 aliasIndex = 1;
  for (char** alias = remoteHost->h_aliases; *alias; ++alias) {
    LOG(Info) << "  Alias: (" << aliasIndex << ") " << alias;
  }

  nu::String addressType;
  switch (remoteHost->h_addrtype) {
    case AF_INET:
      addressType = "AF_INET";
      break;

    case AF_NETBIOS:
      addressType = "AF_NETBIOS";
      break;

    default:
      addressType = "unknown";
      break;
  }
  LOG(Info) << "  Address type: " << addressType;

  LOG(Info) << "  Address length: " << remoteHost->h_length;

  if (remoteHost->h_addrtype == AF_INET) {
    in_addr addr = {0, 0, 0, 0};
    I32 addrIndex = 0;
    while (remoteHost->h_addr_list[addrIndex]) {
      addr.s_addr = *(u_long*)remoteHost->h_addr_list[addrIndex];
      ++addrIndex;
      LOG(Info) << "  IP Address: (" << addrIndex << ") " << inet_ntoa(addr);
    }
  } else if (remoteHost->h_addrtype == AF_NETBIOS) {
    printf("NETBIOS address was returned\n");
  }

  auto firstAddr = reinterpret_cast<U8*>(remoteHost->h_addr_list[0]);
  return {firstAddr[0], firstAddr[1], firstAddr[2], firstAddr[3]};
}

}  // namespace fi
