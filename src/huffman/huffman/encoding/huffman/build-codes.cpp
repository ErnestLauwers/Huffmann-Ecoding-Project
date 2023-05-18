#include <vector>
#include "data/binary-tree.h"
#include "util.h"

std::vector<std::vector<Datum>> build_codes(const data::Node<std::pair<Datum, unsigned long long int>>& tree)
{
    std::vector<std::vector<Datum>> codes;
    std::vector<Datum> currentCode;

    std::function<void(const data::Node<std::pair<Datum, unsigned long long int>>&, const std::vector<Datum>&)> traverseTree =
        [&](const data::Node<std::pair<Datum, unsigned long long int>>& node, const std::vector<Datum>& currentCode)
    {
        const auto* leaf = dynamic_cast<const data::Leaf<std::pair<Datum, unsigned long long int>>*>(&node);
        if (leaf != nullptr)
        {
            Datum value = leaf->get_value().first;
            codes[value] = currentCode;
        }
        else
        {
            const auto* branch = dynamic_cast<const data::Branch<std::pair<Datum, unsigned long long int>>*>(&node);
            if (branch != nullptr)
            {
                std::vector<Datum> leftCode = currentCode;
                leftCode.push_back(0);
                traverseTree(branch->get_left_child(), leftCode);

                std::vector<Datum> rightCode = currentCode;
                rightCode.push_back(1);
                traverseTree(branch->get_right_child(), rightCode);
            }
        }
    };

    constexpr Datum maxDatum = std::numeric_limits<Datum>::max();
    codes.resize(maxDatum + 1);

    traverseTree(tree, currentCode);

    return codes;
}