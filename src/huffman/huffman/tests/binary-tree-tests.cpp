#ifdef TEST_BUILD

#include "data/binary-tree.h"
#include "catch.hpp"
#include <type_traits>

namespace 
{
    void check_leaf(int value, int expected_weight) {
        auto leaf = std::make_unique<data::Leaf<int>>(value);
        CHECK(leaf->get_value() == expected_weight);
    }

    void check_branch(int a, int b, int expected_weight) {
        auto left_child = std::make_unique<data::Leaf<int>>(a);
        auto right_child = std::make_unique<data::Leaf<int>>(b);
        auto branch = std::make_unique<data::Branch<int>>(left_child, right_child);
        CHECK(branch->weight() == expected_weight);
    }
}

TEST_CASE("Binary tree tests")
{
    check_leaf(3, 3);
    check_leaf(1, 1);

    check_branch(1, 4, 5);
    check_branch(6, 3, 9);
    check_branch(10, 67, 77);
}

#endif