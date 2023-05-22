/*#ifdef TEST_BUILD

#include "catch.hpp"
#include "data/binary-tree.h"
#include "encoding/huffman/tree-encoding.h"

namespace
{
    bool areTreesEqual(const data::Node<Datum>& node1, const data::Node<Datum>& node2)
    {
        bool isNode1Leaf = dynamic_cast<const data::Leaf<Datum>*>(&node1) != nullptr;
        bool isNode2Leaf = dynamic_cast<const data::Leaf<Datum>*>(&node2) != nullptr;

        if (isNode1Leaf != isNode2Leaf)
            return false;

        if (isNode1Leaf && isNode2Leaf)
        {
            const auto& leaf1 = dynamic_cast<const data::Leaf<Datum>&>(node1);
            const auto& leaf2 = dynamic_cast<const data::Leaf<Datum>&>(node2);

            return leaf1.get_value() == leaf2.get_value();
        }

        const auto& branch1 = dynamic_cast<const data::Branch<Datum>&>(node1);
        const auto& branch2 = dynamic_cast<const data::Branch<Datum>&>(node2);

        return areTreesEqual(branch1.get_left_child(), branch2.get_left_child()) && areTreesEqual(branch1.get_right_child(), branch2.get_right_child());
    }

    void check_tree_encoding()
    {
        io::MemoryBuffer<8> buffer;

        auto leaf1 = std::make_unique<data::Leaf<Datum>>(10);
        auto leaf2 = std::make_unique<data::Leaf<Datum>>(15);
        auto leaf3 = std::make_unique<data::Leaf<Datum>>(14);
        auto leaf4 = std::make_unique<data::Leaf<Datum>>(16);
        auto leaf5 = std::make_unique<data::Leaf<Datum>>(12);
        auto leaf6 = std::make_unique<data::Leaf<Datum>>(19);

        auto branch1 = std::make_unique<data::Branch<Datum>>(std::move(leaf1), std::move(leaf2));
        auto branch2 = std::make_unique<data::Branch<Datum>>(std::move(leaf3), std::move(leaf4));
        auto branch3 = std::make_unique<data::Branch<Datum>>(std::move(leaf5), std::move(leaf6));
        auto branch4 = std::make_unique<data::Branch<Datum>>(std::move(branch1), std::move(branch2));

        auto original_tree = data::Branch<Datum>(std::move(branch3), std::move(branch4));

        auto output = buffer.destination()->create_output_stream();
        auto input = buffer.source()->create_input_stream();

        encoding::huffman::encode_tree(original_tree, 8, *output);
        auto decoded_tree = encoding::huffman::decode_tree(8, *input);

        CHECK(!areTreesEqual(original_tree, *decoded_tree));
    }
}

TEST_CASE("Tree Encoding Tests")
{
    check_tree_encoding();
}

#endif*/