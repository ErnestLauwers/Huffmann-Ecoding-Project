#ifndef BINARY_IO_H
#define BINARY_IO_H
#include "io/streams.h"
#include <cstdlib>
#include "io/memory-buffer.h"
#include "io/files.h"

namespace encoding
{
    class EncodingImplementation
    {
    public:
        virtual ~EncodingImplementation() {}

        virtual void encode(io::InputStream& input, io::OutputStream& output) = 0;
        virtual void decode(io::InputStream& input, io::OutputStream& output) = 0;
    };

    template <typename IN, typename OUT>
    class Encoding 
    {
    private:
        std::unique_ptr<EncodingImplementation> implementation;
    public:
        Encoding(std::unique_ptr<EncodingImplementation> impl) : implementation(std::move(implementation)) {}

        std::unique_ptr<EncodingImplementation>& operator->() { return implementation; }
        const std::unique_ptr<EncodingImplementation>& operator->() const { return implementation; }

        void encode(const io::DataSource<IN>&source, const Encoding<IN, OUT>&encoding, const io::DataDestination<OUT>&destination)
        {
            static_assert(IN == encoding.input_domain_size());
            static_assert(OUT == encoding.output_domain_size());

            auto input_stream = source.create_input_stream();
            auto output_stream = destination.create_output_stream();

            encoding->encode(*input_stream, *output_stream);
        }

        void decode(const io::DataSource<OUT>& source, const Encoding<IN, OUT>& encoding, const io::DataDestination<IN>& destination)
        {
            static_assert(IN == encoding.input_size());
            static_assert(OUT == encoding.output_size());

            auto input_stream = source.create_input_stream();
            auto output_stream = destination.create_output_stream();

            encoding->decode(*input_stream, *output_stream);
        }
    };
}

#endif