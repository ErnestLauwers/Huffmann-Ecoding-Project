#ifdef TEST_BUILD

#include "catch.hpp"
#include "encoding/bit-grouper.h"
#include "encoding/encoding.h"
#include "io/binary-io.h"

namespace
{
	void check_bit_grouper(int expected_size)
	{
		io::MemoryBuffer<2> buffer1;
		io::MemoryBuffer<1 << 2> buffer2;

		buffer1.data()->push_back(1);
		buffer1.data()->push_back(1);
		buffer1.data()->push_back(1);
		buffer1.data()->push_back(0);

		encoding::encode<2, 1 << 2>(buffer1.source(), encoding::bit_grouper<2>(), buffer2.destination());

		CHECK(buffer2.data()->front() == expected_size);
	}
}

TEST_CASE("Bit Grouper Tests")
{
	check_bit_grouper(0);
}

#endif