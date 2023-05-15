#ifndef EOF_ENCODING_H
#define EOF_ENCODING_H
#include "encoding.h"
#include "util.h"

std::shared_ptr<encoding::EncodingImplementation> create_eof_implementation(u64 domain_size);

namespace encoding
{
	template<u64 N>
	encoding::Encoding<N, N + 1> eof_encoding()
	{
		return Encoding<N, N + 1>(create_eof_implementation(N));
	}
}

#endif