#ifndef HUFFMAN_DECODING_H
#define HUFFMAN_DECODING_H
#include "data/binary-tree.h"
#include "io/streams.h"

Datum decode_single_datum(io::InputStream& input, const data::Node<Datum>& tree);
void decode_bits(io::InputStream& input, const data::Node<Datum>& tree, io::OutputStream& ouptut);

#endif