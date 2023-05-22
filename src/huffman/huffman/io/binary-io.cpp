#include "io/binary-io.h"

u64 io::read_bits(unsigned nbits, io::InputStream& input) {
    u64 res = 0;
    while (nbits != 0) {
        if (!input.end_reached()) {
            res |= (input.read() << (nbits - 1));
        }
        else {
            res |= 0;
        }
        --nbits;
    }
    return res;
}
void io::write_bits(u64 value, unsigned nbits, io::OutputStream& output) {
    unsigned count = nbits;

    while (nbits != 0) {
        output.write((value >> (nbits - 1)) & 1);
        --count;
        --nbits;
    }
}
