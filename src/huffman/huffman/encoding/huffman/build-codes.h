#ifndef BUILD_CODES_H
#define BUILD_CODES_H

#include "data/binary-tree.h"
#include <vector>
#include "util.h"

std::unique_ptr<std::vector<std::vector<Datum>>> build_codes(const data::Node<std::pair<Datum, u64>>& tree, const u64 domain_size);

#endif