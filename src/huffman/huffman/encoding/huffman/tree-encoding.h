#ifndef TREE_ENCODING_H
#define TREE_ENCODING_H
#include "data/binary-tree.h"
#include "io/memory-buffer.h"
#include "util.h"

namespace encoding
{
	namespace huffman
	{
		void encode_tree(const data::Node<Datum>& root, unsigned bits, io::OutputStream& output);

		std::unique_ptr<data::Node<Datum>> decode_tree(unsigned bits, io::InputStream& input);
	}
}

#endif