#ifdef TEST_BUILD

#include "encoding/huffman/build-tree.h"
#include "catch.hpp"
#include "data/binary-tree.h"

namespace
{
	void check_build_tree_weight_leaf()
	{
		data::Leaf<std::pair<Datum, u64>> leaf(std::make_pair(Datum(), 10));

		const u64 weight = encoding::huffman::calculate_weight(leaf);

		CHECK(weight == 10);
	}

	void check_build_tree_weight_branch()
	{
		auto left_leaf = std::make_unique<data::Leaf<std::pair<Datum, u64>>>(std::make_pair(Datum(), 5));
		auto right_leaf = std::make_unique<data::Leaf<std::pair<Datum, u64>>>(std::make_pair(Datum(), 7));
		data::Branch<std::pair<Datum, u64>> branch(std::move(left_leaf), std::move(right_leaf));

		const u64 weight = encoding::huffman::calculate_weight(branch);

		CHECK(weight == 12);
	}

	bool is_same(const data::Node<std::pair<Datum, unsigned long long int>>& node, data::FrequencyTable<Datum> table) {
		auto leaf = dynamic_cast<const data::Leaf<std::pair<Datum, unsigned long long int>>*>(&node);
		if (leaf != nullptr)
		{
			const auto value = leaf->get_value();
			return table[value.first] == value.second;
		}
		else
		{
			auto branch = dynamic_cast<const data::Branch<std::pair<Datum, unsigned long long int>>*> (&node);
			return is_same(branch->get_left_child(), table) && is_same(branch->get_right_child(), table);
		}
	}

    void check_build_tree_valid()
    {
		data::FrequencyTable<Datum> frequency_table;

		frequency_table.increment('A');
		frequency_table.increment('B');
		frequency_table.increment('A');
		frequency_table.increment('C');
		
		auto tree = encoding::huffman::build_tree(frequency_table);
		CHECK(is_same(*(tree.get()), frequency_table));
    }
}

TEST_CASE("Build Tree Tests")
{
	check_build_tree_weight_leaf();
	check_build_tree_weight_branch();
	check_build_tree_valid();
}

#endif