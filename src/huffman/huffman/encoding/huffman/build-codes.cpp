#include <vector>
#include "data/binary-tree.h"
#include "util.h"

std::unique_ptr<std::vector<std::vector<Datum>>> build_codes(const data::Node<std::pair<Datum, u64>>& tree, const u64 size)
{
    std::vector<std::vector<Datum>> all_codes(size);

    std::function<void(const data::Node<std::pair<Datum, u64>>&, std::vector<Datum>)> traverse = [&](const data::Node<std::pair<Datum, u64>>& node, std::vector<Datum> bits) {
        if (const auto* leaf = dynamic_cast<const data::Leaf<std::pair<Datum, u64>>*>(&node))
        {
            all_codes[leaf->get_value().first] = bits;
        }
        else if (const auto* branch = dynamic_cast<const data::Branch<std::pair<Datum, u64>>*>(&node))
        {
            std::vector<Datum> left_bits = bits;
            left_bits.push_back(0);
            traverse(branch->get_left_child(), left_bits);

            std::vector<Datum> right_bits = bits;
            right_bits.push_back(1);
            traverse(branch->get_right_child(), right_bits);
        }
    };

    traverse(tree, {});

    return std::make_unique<std::vector<std::vector<Datum>>>(std::move(all_codes));
}
