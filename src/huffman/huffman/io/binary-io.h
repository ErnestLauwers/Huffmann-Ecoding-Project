#ifndef BINARY_IO_H
#define BINARY_IO_H

#include "io/streams.h"
#include <cstdint>

namespace io 
{
    void write_bits(u64 value, unsigned bits, OutputStream& output);

    u64 read_bits(unsigned bits, InputStream& input);
}

#endif