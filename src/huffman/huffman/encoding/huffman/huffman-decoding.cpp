#include "huffman-decoding.h"
#include "io/streams.h";
#include "data/binary-tree.h"



Datum decode_single_datum(io::InputStream& input, const data::Node<Datum>& tree)
{
	auto branch = dynamic_cast<const data::Branch<Datum>*>(&tree);

	if (branch != nullptr)
	{
		if (input.end_reached())
		{
			return 0;
		}
		else {
			auto bit = input.read();
			if (bit == 0)
			{
				return decode_single_datum(input, branch->get_left_child());
			}
			else if (bit == 1)
			{
				return decode_single_datum(input, branch->get_right_child());
			}
		}

	}
	else {
		auto leaf = static_cast<const data::Leaf<Datum>&> (tree);
		return leaf.get_value();
	}
}










void decode_bits(io::InputStream& input, const  data::Node<Datum>& tree, io::OutputStream& output)
{
	while (!input.end_reached())
	{
		output.write(decode_single_datum(input, tree));
	}
}
