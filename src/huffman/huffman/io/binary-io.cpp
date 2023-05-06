#include "io/binary-io.h"
#include <cstdint>

namespace io {

    u64 io::read_bits(unsigned nbits, io::InputStream& input)
    {
        u64 result = 0;
        unsigned bits_read = 0;
        while (bits_read < nbits) {
            int bit = input.read();
            if (bit == io::InputStream::Eof) {
                bit = 0;
            }
            result = (result << 1) | bit;
            bits_read++;
        }
        result <<= (64 - nbits); // Shift the result to the left to fill unused bits with 0s
        return result;
    }

}