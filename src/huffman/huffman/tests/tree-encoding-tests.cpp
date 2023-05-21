#ifdef TEST_BUILD

#include "catch.hpp"
#include "data/binary-tree.h"
#include "encoding/huffman/tree-encoding.h"
#include <iostream>

namespace
{


	void check_tree_encoding()
	{
		auto leaf1 = std::make_unique<data::Leaf<Datum>>(10);
		auto leaf2 = std::make_unique<data::Leaf<Datum>>(15);
		auto leaf3 = std::make_unique<data::Leaf<Datum>>(14);
		auto leaf4 = std::make_unique<data::Leaf<Datum>>(16);
		auto leaf5 = std::make_unique<data::Leaf<Datum>>(12);
		auto leaf6 = std::make_unique<data::Leaf<Datum>>(19);

		auto branch1 = std::make_unique<data::Branch<Datum>>(std::move(leaf1), std::move(leaf2));
		auto branch2 = std::make_unique<data::Branch<Datum>>(std::move(leaf3), std::move(leaf4));
		auto branch3 = std::make_unique<data::Branch<Datum>>(std::move(leaf5), std::move(leaf6));
		auto branch12 = std::make_unique<data::Branch<Datum>>(std::move(branch1), std::move(branch2));
		auto branch123 = data::Branch<Datum>(std::move(branch12), std::move(branch3));

		io::MemoryBuffer<8> buffer;

		auto output = buffer.destination()->create_output_stream();
		encoding::huffman::encode_tree(branch123, 8, (*output));

		auto input = buffer.source()->create_input_stream();
		auto boom = encoding::huffman::decode_tree(8, (*input));

		auto root = dynamic_cast<const data::Branch<Datum>*> (boom.get());

		auto left_1 = dynamic_cast<const data::Branch<Datum>*> (&(root->get_left_child()));
		auto right_1 = dynamic_cast<const data::Branch<Datum>*> (&(root->get_right_child()));

		CHECK(encoding::huffman::equal(*(boom.get()), branch123));

	}	
}

TEST_CASE("Tree Encoding Tests")
{
    check_tree_encoding();
}

#endif