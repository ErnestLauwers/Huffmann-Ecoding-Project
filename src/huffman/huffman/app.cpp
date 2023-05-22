#ifndef TEST_BUILD

#include "encoding/huffman/huffman-encoding.h"
#include "encoding/bit-grouper.h"
#include "encoding/eof-encoding.h"
#include "io/files.h"
#include "encoding/encoding-combiner.h"
#include <iostream>

int main(int argc, char* argv[])
{
    if (argc < 4) {
        std::cerr << "Usage: huffman compress <input_file> <output_file> OR huffman decompress <input_file> <output_file>\n";
        return 1;
    }

    std::string mode = argv[2];
    std::string input_file_path = argv[3];
    std::string output_file_path = argv[4];

    if (mode == "compress") {
        auto input = io::create_file_data_source(input_file_path);
        auto output = io::create_file_data_destination(output_file_path);

        auto eof_encoding = encoding::eof_encoding<256>();
        auto huffman_encoding = encoding::huffman::huffman_encoding<257>();
        auto bit_grouper = encoding::bit_grouper<8>();

        auto encoding = eof_encoding | huffman_encoding | bit_grouper;

        auto input_stream = input->create_input_stream();
        auto output_stream = output->create_output_stream();

        encoding->encode(*input_stream, *output_stream);

        std::cout << "Compression completed.\n";
    }
    else if (mode == "decompress") {
        auto input = io::create_file_data_source(input_file_path);
        auto output = io::create_file_data_destination(output_file_path);

        const auto eof_encoding = encoding::eof_encoding<256>();
        const auto huffman_encoding = encoding::huffman::huffman_encoding<257>();
        const auto bit_grouper = encoding::bit_grouper<8>();

        const auto encoding = eof_encoding | huffman_encoding | bit_grouper;

        const auto input_stream = input->create_input_stream();
        const auto output_stream = output->create_output_stream();

        encoding->decode(*input_stream, *output_stream);

        std::cout << "Decompression completed.\n";
    }
    else {
        std::cerr << "Invalid mode. Please use 'compress' or 'decompress'.\n";
        return 1;
    }
    return 0;
}

#endif