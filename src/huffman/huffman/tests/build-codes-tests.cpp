/*#ifdef TEST_BUILD

#include "catch.hpp"
#include "encoding/huffman/build-codes.h"
#include "encoding/huffman/build-tree.h"
#include <iostream>

namespace
{
	void check_build_codes()
	{
        auto frequency_table = std::make_shared<data::FrequencyTable<Datum>>();
        
        frequency_table->increment(1);
        frequency_table->increment(2);
        frequency_table->increment(2);
        frequency_table->increment(3);
        frequency_table->increment(3);
        frequency_table->increment(3);

        auto root = std::move(encoding::huffman::build_tree(*frequency_table));

        auto codes = build_codes(*root);
        std::cout << "Number of codes: " << codes.size() << std::endl;
        CHECK(codes.size() == 2);
	}
}

TEST_CASE("Build Codes Tests")
{
    check_build_codes();
}

#endif*/