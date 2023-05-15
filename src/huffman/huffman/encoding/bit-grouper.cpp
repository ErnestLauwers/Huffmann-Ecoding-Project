#include "bit-grouper.h"
#include "encoding.h"
#include "io/binary-io.h"

namespace
{
    class BitGrouperImplementation : public encoding::EncodingImplementation
    {
    private:
        u64 group_size;
    public:
        BitGrouperImplementation(u64 size) : group_size(size) {}

        void encode(io::InputStream& input, io::OutputStream& output) override
        {
            while (!input.end_reached())
            {
                u64 bits = io::read_bits(group_size, input);
                output.write(bits);
            }
        }

        void decode(io::InputStream& input, io::OutputStream& output) override
        {
            while (!input.end_reached())
            {
                io:write_bits(input.read(), group_size, output);
            }
        }
    };
}

std::shared_ptr<encoding::EncodingImplementation> create_bit_grouper_implementation(unsigned size)
{
    return std::make_shared<BitGrouperImplementation>(size);
}