#include <cstdint>
#ifndef UTIL_H
#define UTIL_H
#include <cstdint>
#include <memory>
#include <functional> 

namespace data
{
    template<typename T>
    class Node 
    {
    public:
        virtual ~Node() {}
        virtual uint32_t weight() const = 0;
    };

    template<typename T>
    class Branch : public Node<T>
    {
    private:
        std::unique_ptr<Node<T>> left_child_ptr;
        std::unique_ptr<Node<T>> right_child_ptr;
    public:
        Branch(std::unique_ptr<Node<T>> left_child, std::unique_ptr<Node<T>> right_child)
            : left_child_ptr(std::move(left_child)), right_child_ptr(std::move(right_child))
        {
            assert(left_child_ptr->weight() >= 0 && right_child_ptr->weight() >= 0);
        }

        const Node<T>& left_child() const {
            return *left_child_ptr;
        }

        const Node<T>& right_child() const {
            return *right_child_ptr;
        }

        uint32_t weight() const override {
            return left_child().weight() + right_child().weight();
        }
    };

    template<typename T>
    class Leaf : public Node<T> 
    {
    private:
        T data;
    public:
        Leaf(const T& value) : data(value) {}

        const T& get_value() const { return data; }

        uint32_t weight() const override { return 1; }
    };

    
}

#endif
