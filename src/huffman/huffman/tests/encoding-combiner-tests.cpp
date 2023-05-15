#ifdef TEST_BUILD

#include "catch.hpp"
#include "encoding/bit-grouper.h"
#include "encoding/encoding.h"
#include "io/binary-io.h"
#include "encoding/eof-encoding.h"
#include "encoding/encoding-combiner.h"

namespace
{
	void check_combiner_1()
	{

		io::MemoryBuffer<256> buffer1;
		io::MemoryBuffer<258> buffer2;
		io::MemoryBuffer<256> buffer3;

		buffer1.data()->push_back(187);
		buffer1.data()->push_back(19);
		buffer1.data()->push_back(1);
		buffer1.data()->push_back(43);
		buffer1.data()->push_back(0);
		buffer1.data()->push_back(90);
		buffer1.data()->push_back(203);
		buffer1.data()->push_back(24);

		auto encodings_combined = encoding::eof_encoding<256>() | encoding::eof_encoding<257>();
		encode(buffer1.source(), encodings_combined, buffer2.destination());
		decode(buffer2.source(), encodings_combined, buffer3.destination());

		CHECK((*buffer1.data()) == (*buffer3.data()));
	}

	void check_combiner_2()
	{
		io::MemoryBuffer<256> buffer1;
		io::MemoryBuffer<258> buffer2;

		buffer1.data()->push_back(1);
		buffer1.data()->push_back(1);
		buffer1.data()->push_back(1);
		buffer1.data()->push_back(0);
		buffer1.data()->push_back(1);
		buffer1.data()->push_back(0);
		buffer1.data()->push_back(1);
		buffer1.data()->push_back(0);

		auto encodings_combined = encoding::eof_encoding<256>() | encoding::eof_encoding<257>();
		encode(buffer1.source(), encodings_combined, buffer2.destination());

		CHECK((*buffer2.data())[0] == 1);
		CHECK((*buffer2.data())[1] == 1);
		CHECK((*buffer2.data())[2] == 1);
		CHECK((*buffer2.data())[3] == 0);
		CHECK((*buffer2.data())[4] == 1);
		CHECK((*buffer2.data())[5] == 0);
		CHECK((*buffer2.data())[6] == 1);
		CHECK((*buffer2.data())[7] == 0);
	}
}

TEST_CASE("Encoding Combiner Tests")
{
	check_combiner_1();
	check_combiner_2();
}

#endif