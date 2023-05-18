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
    
    void check_map() {
        auto left_child = std::make_unique<data::Leaf<int>>(5);
        auto right_child = std::make_unique<data::Leaf<int>>(3);
        data::Branch<int> branch(std::move(left_child), std::move(right_child));
        const data::Leaf<int>* left_child_2 = dynamic_cast<const data::Leaf<int>*> (&branch.get_left_child());
        const data::Leaf<int>* right_child_2 = dynamic_cast<const data::Leaf<int>*> (&branch.get_right_child());

        std::function<double(const int&)> function = [](const int& integer)
        {
            return integer * 5.0;
        };

        auto binary_tree = data::map<int, int>(branch, function);
        auto branch2 = dynamic_cast<data::Branch<int>*> (binary_tree.get());

        const data::Leaf<int>* left_child_3 = dynamic_cast<const data::Leaf<int>*> (&branch2->get_left_child());
        const data::Leaf<int>* right_child_3 = dynamic_cast<const data::Leaf<int>*> (&branch2->get_right_child());

        CHECK(left_child_2->get_value() == 5);
        CHECK(right_child_2->get_value() == 3);
        CHECK(left_child_3->get_value() == 25);
        CHECK(right_child_3->get_value() == 15);
    }
}

TEST_CASE("Binary tree tests")
{
    check_leaf(3, 3);
    check_leaf(1, 1);
    
    check_branch(1, 4, 5);
    check_branch(6, 3, 9);
    check_branch(10, 67, 77);
    
    check_map();
}

#endif