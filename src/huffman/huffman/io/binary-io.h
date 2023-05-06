#ifndef UTIL_H
#define UTIL_H

#include "io/streams.h"
#include <cstdint>

typedef uint64_t u64;

namespace io {
    u64 read_bits(unsigned nbits, InputStream& input);
}

#endif