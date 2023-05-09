#include "encoding.h"
#include "eof-encoding.h"

namespace
{
	class EofEncodingImplementation : public encoding::EncodingImplementation
	{
	private:
		const u64 domain_size;
	public:
		EofEncodingImplementation(u64 domain_size) : domain_size(domain_size) {}

		void encode(io::InputStream& input, io::OutputStream& output) override
		{
			while (!input.end_reached())
			{
				output.write(input.read());
			}
			output.write(domain_size);
		}

		void decode(io::InputStream& input, io::OutputStream& output) override
		{
			while (!input.end_reached())
			{
				Datum symbol = input.read();
				if (symbol == domain_size)
				{
					break;
				}
				output.write(symbol);
			}
		}
	};

}


EofEncodingImplementation* create_eof_implementation(u64 domain_size)
{
	return new EofEncodingImplementation(domain_size);
}