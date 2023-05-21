/*#ifdef TEST_BUILD

#include "encoding/huffman/huffman-decoding.h"
#include "catch.hpp"
#include "io/memory-buffer.h"

namespace
{
    void check_huffman_decoding()
    {
        // Create a test input stream
        std::vector<unsigned char> inputBuffer = { 0x02, 0x01, 0x01 }; // 00000010 00000001 00000001
        io::MemoryBuffer<8> inputMemoryBuffer(inputBuffer);
        io::InputStream& input = *inputMemoryBuffer.source();

        // Create a test output stream
        std::vector<unsigned char> outputBuffer;
        io::MemoryBuffer<8> outputMemoryBuffer(outputBuffer);
        io::OutputStream& output = *outputMemoryBuffer.destination();

        // Create a test tree
        auto leaf1 = std::make_unique<data::Leaf<Datum>>(10);
        auto leaf2 = std::make_unique<data::Leaf<Datum>>(15);
        auto leaf3 = std::make_unique<data::Leaf<Datum>>(14);
        auto leaf4 = std::make_unique<data::Leaf<Datum>>(16);
        auto branch1 = std::make_unique<data::Branch<Datum>>(std::move(leaf1), std::move(leaf2));
        auto branch2 = std::make_unique<data::Branch<Datum>>(std::move(leaf3), std::move(leaf4));
        auto tree = data::Branch<Datum>(std::move(branch1), std::move(branch2));

        // Call the function to decode bits
        decode_bits(input, tree, output);

        // Verify the output
        std::vector<unsigned char> expectedOutput = { 0x0E, 0x10 }; // 00001110 00010000
        REQUIRE(outputBuffer == expectedOutput);
    }
}

TEST_CASE("Huffman Decoding Tests")
{
    check_huffman_decoding();
}

#endif
*/