#ifndef BUILD_TREE_H
#define BUILD_TREE_H

namespace encoding
{
	namespace huffman
	{
		const u64 calculate_weight(const data::Node<std::pair<Datum, u64>>& node);
		std::unique_ptr<data::Node<std::pair<Datum, unsigned long long int>>> build_tree(const data::FrequencyTable<Datum>& frequency_table);
	}
}

#endif