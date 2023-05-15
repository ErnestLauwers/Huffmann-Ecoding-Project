#ifndef ENCODING_H
#define ENCODING_H
#include <io/memory-buffer.h>

namespace encoding
{
    class EncodingImplementation
    {
    public:
        virtual ~EncodingImplementation() {}

        virtual void encode(io::InputStream& input, io::OutputStream& output) = 0;
        virtual void decode(io::InputStream& input, io::OutputStream& output) = 0;
    };

    template <u64 IN, u64 OUT>
    class Encoding 
    {
    private:
        std::shared_ptr<EncodingImplementation> implementation;
    public:
        Encoding(std::shared_ptr<EncodingImplementation> impl) : implementation(impl) {}

        std::shared_ptr<EncodingImplementation> operator->() { return implementation; }
        const std::shared_ptr<EncodingImplementation> operator->() const { return implementation; }

        constexpr u64 input_domain_size() const { return IN; }
        constexpr u64 output_domain_size() const { return OUT; }
    };
    
    template<u64 IN, u64 OUT>
    void encode(io::DataSource<IN> source, Encoding<IN, OUT> encoding,io::DataDestination<OUT> destination)
    {
        static_assert(IN == encoding.input_domain_size());
        static_assert(OUT == encoding.output_domain_size());

        auto input_stream = source->create_input_stream();
        auto output_stream = destination->create_output_stream();

        encoding->encode(*input_stream, *output_stream);
    }

    template<u64 IN, u64 OUT>
    void decode(io::DataSource<IN> source, Encoding<OUT, IN> decoding, io::DataDestination<OUT> destination)
    {
        static_assert(IN == decoding.output_domain_size());
        static_assert(OUT == decoding.input_domain_size());

        auto input_stream = source->create_input_stream();
        auto output_stream = destination->create_output_stream();

        decoding->decode(*input_stream, *output_stream);
    }
}

#endif