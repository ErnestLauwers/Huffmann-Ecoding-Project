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
        auto branch = std::make_unique<data::Branch<int>>(std::move(left_child), std::move(right_child));
        CHECK(branch->get_left_child().get_value() + branch->get_right_child().get_value() == expected_weight);
    }
    /*
    void check_map() {
        auto left_child_1 = std::make_unique<data::Leaf<int>>(5);
        auto right_child_1 = std::make_unique<data::Leaf<int>>(3);
        auto branch_1 = std::make_unique<data::Branch<int>>(std::move(left_child_1), std::move(right_child_1));

        auto left_child_2 = std::make_unique<data::Leaf<int>>(4);
        auto right_child_2 = std::make_unique<data::Leaf<int>>(2);
        auto branch_2 = std::make_unique<data::Branch<int>>(std::move(left_child_2), std::move(right_child_2));

        auto branch_3 = std::make_unique<data::Branch<int>>(std::move(branch_1), std::move(branch_2));
        auto square_function = [](const int& x) { return x * x; };
        auto new_branch = data::map(*branch_3, square_function);
    }*/
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