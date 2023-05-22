#ifndef ENCODING_COMBINER_H
#define ENCODING_COMBINER_H
#include "encoding.h"
#include "io/memory-buffer.h"
#include "util.h"

namespace encoding
{
	template<u64 N1, u64 N2, u64 N3>
	class EncodingCombinerImplementation : public encoding::EncodingImplementation
	{
	private:
		const Encoding<N1, N2> E1;
		const Encoding<N2, N3> E2;
	public:
		EncodingCombinerImplementation(Encoding<N1, N2> E12, Encoding<N2, N3> E22) : E1(E12), E2(E22) { }

		void encode(io::InputStream& in, io::OutputStream& out)
		{
			io::MemoryBuffer<N2> memory_buffer;

			E1->encode(in, *(memory_buffer.destination()->create_output_stream()));

			E2->encode(*(memory_buffer.source()->create_input_stream()), out);
		}
		void decode(io::InputStream& in, io::OutputStream& out)
		{
			io::MemoryBuffer<N2> memory_buffer;

			E2->decode(in, *(memory_buffer.destination()->create_output_stream()));

			E1->decode(*(memory_buffer.source()->create_input_stream()), out);
		}
	};

	template<u64 N1, u64 N2, u64 N3>
	Encoding<N1, N3> operator | (const encoding::Encoding<N1, N2> E1, const encoding::Encoding<N2, N3> E2)
	{
		return Encoding<N1, N3>(std::make_shared<EncodingCombinerImplementation<N1, N2, N3>>(E1, E2));
	}
}

#endif