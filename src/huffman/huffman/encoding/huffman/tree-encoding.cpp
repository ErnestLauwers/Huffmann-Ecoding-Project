#include "tree-encoding.h"
#include "io/memory-buffer.h"
#include "data/binary-tree.h"
#include "io/binary-io.h"
#include "util.h"

namespace encoding
{
	namespace huffman
	{
		std::unique_ptr<data::Node<Datum>> decode_tree(unsigned bits, io::InputStream& input)
		{
			if (input.read() == 1)
			{
				auto left_child = decode_tree(bits, input);
				auto right_child = decode_tree(bits, input);

				auto branch = data::Branch<Datum>(std::move(left_child), std::move(right_child));
				return std::move(std::make_unique<data::Branch<Datum>>(std::move(branch)));
			}
			else
			{
				auto bits2 = io::read_bits(bits, input);
				auto leaf = std::make_unique<data::Leaf<Datum>>(bits2);

				return std::move(leaf);
			}
		}

		void encode_tree(const data::Node<Datum>& root, unsigned bits, io::OutputStream& output)
		{
			if (const auto branch = dynamic_cast<const data::Branch<Datum>*>(&root))
			{
				io::write_bits(1, 1, output);
				encode_tree(branch->get_left_child(), bits, output);
				encode_tree(branch->get_right_child(), bits, output);
			}
			else if (const auto leaf = dynamic_cast<const data::Leaf<Datum>*>(&root))
			{
				io::write_bits(0, 1, output);
				io::write_bits(leaf->get_value(), bits, output);
			}
		}

		bool equal(const data::Node<Datum>& a, const data::Node<Datum>& b) {
			auto leaf_a = dynamic_cast<const data::Leaf<Datum>*> (&a);
			auto branch_a = dynamic_cast<const data::Branch<Datum>*> (&a);
			auto leaf_b = dynamic_cast<const data::Leaf<Datum>*> (&b);
			auto branch_b = dynamic_cast<const data::Branch<Datum>*> (&b);

			if (leaf_a != nullptr && leaf_b != nullptr) {
				return leaf_a->get_value() == leaf_b->get_value();
			}
			else if (branch_a != nullptr && branch_b != nullptr) {
				return equal(branch_a->get_left_child(), branch_b->get_left_child()) && equal(branch_a->get_right_child(), branch_b->get_right_child());
			}
			else {
				return false;
			}
		}
	}
}