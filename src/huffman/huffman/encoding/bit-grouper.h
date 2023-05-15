#ifndef BIT_GROUPER_H
#define BIT_GROUPER_H
#include "util.h"
#include "encoding.h"

std::shared_ptr<encoding::EncodingImplementation> create_bit_grouper_implementation(unsigned size);

namespace encoding
{
	template<unsigned GROUP_SIZE>
	encoding::Encoding<2, 1 << GROUP_SIZE>bit_grouper()
	{
		return Encoding<2, 1 << GROUP_SIZE>(create_bit_grouper_implementation(GROUP_SIZE));
	}
}

#endif