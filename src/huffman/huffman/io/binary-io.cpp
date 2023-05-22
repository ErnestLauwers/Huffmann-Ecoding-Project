#include "io/binary-io.h"

void io::write_bits(u64 value, unsigned bits, io::OutputStream& output) {
    unsigned remaining_bits = bits;

    while (remaining_bits > 0) {
        u64 bit = (value >> (remaining_bits - 1)) & 1;

        output.write(bit);

        --remaining_bits;
    }
}

u64 io::read_bits(unsigned bits, io::InputStream& input) {
    u64 result = 0;

    while (bits > 0) {
        if (!input.end_reached()) {
            result <<= 1;

            result |= input.read();
        }
        else {
            result <<= 1;
        }

        --bits;
    }
    return result;
}
