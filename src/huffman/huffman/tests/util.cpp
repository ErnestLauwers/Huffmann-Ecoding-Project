#ifdef TEST_BUILD

#include "../util.h"
#include "catch.hpp"

namespace
{
    void check_bits(int a, int expected)
    {
        int actual = bits_needed(a);
        CHECK(actual == expected);
    }

    void check_bytes(int a, int expected)
    {
        int actual = bytes_needed(a);
        CHECK(actual == expected);
    }
}

TEST_CASE("Bits and Bytes needed tests")
{
    check_bits(9, 4);
    check_bits(129, 8);
    check_bytes(257, 2);
    check_bytes(128, 1);
}

#endif