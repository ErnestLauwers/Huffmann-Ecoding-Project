#include "util.h"
#include "io/streams.h"
#include "data/binary-tree.h"
#include "io/binary-io.h"

Datum decode_single_datum(io::InputStream& input, const data::Node<Datum>& tree)
{
    auto branch = dynamic_cast<const data::Branch<Datum>*>(&tree);

    if (branch == nullptr) {
        auto leaf = static_cast<const data::Leaf<Datum>&> (tree);
        return leaf.get_value();
    }
    else {
        if (!input.end_reached()) {
            auto b = input.read();

            if (b == 0) {
                return decode_single_datum(input, branch->get_left_child());
            }
            else {
                return decode_single_datum(input, branch->get_right_child());
            }
        } else {
            return 0;
        }
    }
}

void decode_bits(io::InputStream& input, const data::Node<Datum>& tree, io::OutputStream& output)
{
    while (true)
    {
        Datum datum = decode_single_datum(input, tree);
        if (datum == 0)
        {
            break;
        }
        output.write(datum);
    }
}