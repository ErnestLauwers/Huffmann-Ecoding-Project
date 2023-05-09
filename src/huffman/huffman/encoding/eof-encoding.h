#ifndef EOF_ENCODING_H
#define EOF_ENCODING_H

#include "encoding.h"

namespace encoding
{
	template<u64 N>
	encoding::Encoding<std::integral_constant<u64, N>, std::integral_constant<u64, N + 1>> eof_encoding()
	{

	}

	class EofEncodingImplementation;

	EofEncodingImplementation* create_eof_implementation(u64 domain_size);
}

#endif