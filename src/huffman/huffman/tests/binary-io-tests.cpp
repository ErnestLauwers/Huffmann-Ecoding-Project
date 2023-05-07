#ifdef TEST_BUILD
#include <io/memory-buffer.h>
#include <io/binary-io.h>
#include <catch.hpp>

namespace
{
    void check_read_write(u64 n, unsigned nbits)
    {
        io::MemoryBuffer<2> buffer;
        auto input = buffer.source()->create_input_stream();
        auto output = buffer.destination()->create_output_stream();
        io::write_bits(n, nbits, *output);
        auto result = io::read_bits(nbits, *input);

        REQUIRE(n == result);
    }
}

TEST_CASE("Binary io tests")
{
    check_read_write(0b10101010, 8);
    check_read_write(0, 8);
    check_read_write(UINT64_MAX, 64);
}

#endif