#ifdef TEST_BUILD

#include "catch.hpp"
#include "util.h"
#include "encoding/eof-encoding.h"
#include "io/binary-io.h"
#include "io/memory-buffer.h"
#include <iostream>

namespace
{
	void check_encoding(int expected_size)
	{
		io::MemoryBuffer<17> buffer1;
		io::MemoryBuffer<18> buffer2;

		buffer1.data()->push_back(1);
		buffer1.data()->push_back(2);
		buffer1.data()->push_back(3);
		buffer1.data()->push_back(4);
		buffer1.data()->push_back(5);
		buffer1.data()->push_back(6);
		buffer1.data()->push_back(7);
		buffer1.data()->push_back(8);
		buffer1.data()->push_back(9);
		buffer1.data()->push_back(10);
		buffer1.data()->push_back(11);
		buffer1.data()->push_back(12);
		buffer1.data()->push_back(13);
		buffer1.data()->push_back(14);
		buffer1.data()->push_back(15);
		buffer1.data()->push_back(16);

		encoding::encode(buffer1.source(), encoding::eof_encoding<17>(), buffer2.destination());

		CHECK(buffer2.data()->size() == expected_size);
	}

	void check_decoding(int expected_size)
	{
		io::MemoryBuffer<17> buffer1;
		io::MemoryBuffer<18> buffer2;
		io::MemoryBuffer<17> buffer3;

		buffer1.data()->push_back(1);
		buffer1.data()->push_back(2);
		buffer1.data()->push_back(3);
		buffer1.data()->push_back(4);
		buffer1.data()->push_back(5);
		buffer1.data()->push_back(6);
		buffer1.data()->push_back(7);
		buffer1.data()->push_back(8);
		buffer1.data()->push_back(9);
		buffer1.data()->push_back(10);
		buffer1.data()->push_back(11);
		buffer1.data()->push_back(12);
		buffer1.data()->push_back(13);
		buffer1.data()->push_back(14);
		buffer1.data()->push_back(15);
		buffer1.data()->push_back(16);

		encoding::encode(buffer1.source(), encoding::eof_encoding<17>(), buffer2.destination());
		encoding::decode(buffer2.source(), encoding::eof_encoding<17>(), buffer3.destination());

		CHECK(buffer3.data()->size() == expected_size);
	}
}

TEST_CASE("Eof Encoding Tests")
{
	check_encoding(17);
	check_decoding(16);
}

#endif