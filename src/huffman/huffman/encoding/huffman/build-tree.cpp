#include "data/binary-tree.h"
#include "util.h"
#include "data/frequency-table.h"
#include <iostream>
#include <algorithm>

namespace encoding
{
    namespace huffman
    {
        const u64 calculate_weight(const data::Node<std::pair<Datum, u64>>& node)
        {
            const data::Leaf<std::pair<Datum, u64>>* leaf = dynamic_cast<const data::Leaf<std::pair<Datum, u64>>*>(&node);
            if (leaf != nullptr)
            {
                return leaf->get_value().second;
            }
            else {
                const data::Branch<std::pair<Datum, u64>>* branch = dynamic_cast<const data::Branch<std::pair<Datum, u64>>*>(&node);
                if (branch != nullptr)
                {
                    return calculate_weight(branch->get_left_child()) + calculate_weight(branch->get_right_child());
                }
            }
            return 0;
        }

        std::unique_ptr<data::Node<std::pair<Datum, unsigned long long int>>> build_tree(const data::FrequencyTable<Datum>& frequency_table)
        {
            auto leaves = std::vector<std::unique_ptr<data::Node<std::pair<Datum, unsigned long long int>>>>();
            auto frequency = frequency_table;

            for (Datum value : frequency.values())
            {
                leaves.push_back(std::make_unique<data::Leaf<std::pair<Datum, unsigned long long int>>>(std::make_pair(value, frequency[value])));
            }

            while (leaves.size() != 1)
            {
                std::sort(leaves.begin(), leaves.end(), [](const std::unique_ptr<data::Node<std::pair<Datum, unsigned long long int>>>& x, const std::unique_ptr<data::Node<std::pair<Datum, unsigned long long int>>>& y)
                    {
                        return calculate_weight(*x) > calculate_weight(*y);
                    });
                auto leaf1 = std::move(leaves.back());
                leaves.pop_back();

                auto leaf2 = std::move(leaves.back());
                leaves.pop_back();

                auto branch = std::make_unique<data::Branch<std::pair<Datum, unsigned long long int>>>(std::move(leaf2), std::move(leaf1));
                leaves.push_back(std::move(branch));
            }

            return std::move(leaves.back());
        }
    }
}
