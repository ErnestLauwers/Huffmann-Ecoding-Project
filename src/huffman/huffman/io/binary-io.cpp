#include "io/binary-io.h"
#include <cstdint>

namespace io {
    uint64_t io::read_bits(unsigned nbits, io::InputStream& input) 
    {
        uint64_t bits = 0;
        unsigned i; 
        for (i = 0; i < nbits; i++) {
            Datum datum = input.read();
            int bit = (datum != 0);
            bits = (bits << 1) | bit;
            if (input.end_reached()) {
                nbits = i + 1;
                break;
            }
        }
        bits >>= (nbits - i - 1);
        return bits;
    }

    void io::write_bits(u64 value, unsigned nbits, io::OutputStream& output)
    {
        for (unsigned i = 0; i < nbits; i++) {
            output.write((value >> (nbits - i - 1)) & 1);
        }
    }
}