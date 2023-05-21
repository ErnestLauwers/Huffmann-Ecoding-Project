#ifndef HUFFMAN_ENCODING_H
#define HUFFMAN_ENCODING_H

#include "encoding/encoding.h"
#include "util.h"

namespace encoding 
{
	namespace huffman 
	{
		std::shared_ptr<EncodingImplementation> create_huffman_implementation(unsigned domain_size);

		template<unsigned DOMAIN_SIZE>
		encoding::Encoding<DOMAIN_SIZE, 2>huffman_encoding()
		{
			return Encoding<DOMAIN_SIZE, 2>(create_huffman_implementation(DOMAIN_SIZE));
		}
	}
}

#endif
