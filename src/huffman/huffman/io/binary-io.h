#ifndef BINARY_IO_H
#define BINARY_IO_H

#include "io/streams.h"
#include <cstdint>

namespace io 
{
    u64 read_bits(unsigned nbits, InputStream& input);

    void write_bits(u64 value, unsigned nbits, OutputStream& output);
}

#endif