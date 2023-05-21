#include <vector>
#include "data/binary-tree.h"
#include "util.h"

void helper_function(const data::Node<std::pair<Datum, u64>>& tree, std::vector<Datum> bits, std::vector<std::vector<Datum>>& codes)
{
	const data::Leaf<std::pair<Datum, u64>>* leaf = dynamic_cast<const data::Leaf<std::pair<Datum, u64>>*>(&tree);
	if (leaf != nullptr)
	{
		codes.at(leaf->get_value().first) = bits;
	}

	else {
		const data::Branch<std::pair<Datum, u64>>* branch = dynamic_cast<const data::Branch<std::pair<Datum, u64>>*>(&tree);
		if (branch != nullptr)
		{
			std::vector<Datum> left = bits;
			left.push_back(0);


			std::vector<Datum> right = bits;
			right.push_back(1);


			helper_function(branch->get_left_child(), left, codes);
			helper_function(branch->get_right_child(), right, codes);
		}


	}

}





std::unique_ptr<std::vector<std::vector<Datum>>> build_codes(const data::Node<std::pair<Datum, u64>>& tree, const u64 domain_size)
{

	auto codes = std::make_unique<std::vector<std::vector<Datum>>>(domain_size);
	helper_function(tree, std::vector<Datum>(), *codes);
	return std::move(codes);


}