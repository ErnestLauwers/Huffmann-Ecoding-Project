#include "tree-encoding.h"
#include "io/memory-buffer.h"
#include "data/binary-tree.h"
#include "io/binary-io.h"
#include "util.h"

namespace encoding
{
	namespace huffman
	{
		std::unique_ptr<data::Node<Datum>> decode_tree(Datum nbits, io::InputStream& inputStream)
		{
			if (inputStream.read() == 0)
			{
				Datum data = io::read_bits(nbits, inputStream);

				return std::make_unique<data::Leaf<Datum>>(data);
			}
			else
			{
				std::unique_ptr<data::Node<Datum>> leftNode = decode_tree(nbits, inputStream);
				std::unique_ptr<data::Node<Datum>> rightNode = decode_tree(nbits, inputStream);
				return std::make_unique<data::Branch<Datum>>(std::move(leftNode), std::move(rightNode));
			}
		}

		void encode_tree(const data::Node<Datum>& root, Datum size, io::OutputStream& outputStream)
		{
			if (root.isLeaf())
			{
				const data::Leaf<Datum>& leaf = dynamic_cast<const data::Leaf<Datum>&>(root);
				outputStream.write(0);
				io::write_bits(leaf.get_value(), size, outputStream);
			}
			else
			{
				outputStream.write(1);
				auto& branch = static_cast<const data::Branch<Datum>&>(root);
				encode_tree(branch.get_left_child(), size, outputStream);
				encode_tree(branch.get_right_child(), size, outputStream);
			}
		}
	}
}