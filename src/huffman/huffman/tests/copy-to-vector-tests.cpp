#ifdef TEST_BUILD

#include "catch.hpp"
#include "encoding/huffman/copy-to-vector.h"
#include "io/memory-buffer.h"
#include "io/streams.h"

namespace
{
	void check_copy_to_vector()
	{
		io::MemoryBuffer<2> buffer1;

		buffer1.data()->push_back(4);
		buffer1.data()->push_back(67);
		buffer1.data()->push_back(46);
		buffer1.data()->push_back(23);
		buffer1.data()->push_back(9);

		auto vector = copy_to_vector(*buffer1.source()->create_input_stream());

		CHECK(std::find(vector.begin(), vector.end(), 4) != std::end(vector));
		CHECK(std::find(vector.begin(), vector.end(), 67) != std::end(vector));
		CHECK(std::find(vector.begin(), vector.end(), 46) != std::end(vector));
		CHECK(std::find(vector.begin(), vector.end(), 23) != std::end(vector));
		CHECK(std::find(vector.begin(), vector.end(), 9) != std::end(vector));
	}
}

TEST_CASE("Copy to Vector Tests")
{
	check_copy_to_vector();
}

#endif