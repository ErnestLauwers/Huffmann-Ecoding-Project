#include "encoding/encoding.h"
#include "data/binary-tree.h"
#include "copy-to-vector.h"
#include "data/frequency-table.h"
#include "build-tree.h"
#include "tree-encoding.h"
#include "io/binary-io.h"
#include "build-codes.h"
#include "huffman-decoding.h"

namespace
{
	class HuffmanEncodingImplementation : public encoding::EncodingImplementation
	{
    private:
        u64 domain_size;
    public:
        explicit HuffmanEncodingImplementation(u64 size) : domain_size(size) { };

        void encode(io::InputStream& input, io::OutputStream& output) override
        {
            auto vector = copy_to_vector(input);
            auto frequency = data::count_frequencies<Datum>(vector);
            auto binary_tree = encoding::huffman::build_tree(frequency);
            auto all_codes = build_codes(*binary_tree, domain_size);

            std::function<Datum(const std::pair<Datum, u64>&)> function = [](const std::pair<Datum, u64> i) { return i.first; };
            auto map = data::map(*binary_tree, function);
            encoding::huffman::encode_tree(*map, bits_needed(domain_size), output);

            for (auto value : vector) {
                for (unsigned i = 0; i < all_codes->at(value).size(); ++i) {
                    io::write_bits(all_codes->at(value).at(i), 1, output);
                }
            }
        }

        void decode(io::InputStream& input, io::OutputStream& output) override
        {
            auto tree = encoding::huffman::decode_tree(bits_needed(domain_size), input);
            decode_bits(input, *tree, output);
        }
	};
}

namespace encoding
{
    namespace huffman
    {
        std::shared_ptr<encoding::EncodingImplementation> create_huffman_implementation(unsigned size)
        {
            return std::make_shared<HuffmanEncodingImplementation>(size);
        }
    }
}