
#ifndef FIBER_RESOLVER_H_
#define FIBER_RESOLVER_H_

#include "nucleus/Text/String.h"
#include "fiber/IpAddress.h"

namespace fi {

IpAddress resolve(const nu::String& host) noexcept;

}  // namespace fi

#endif  // FIBER_RESOLVER_H_
