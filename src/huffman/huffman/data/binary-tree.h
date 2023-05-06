#include <cstdint>
#ifndef UTIL_H
#define UTIL_H
#include <memory>
#include <functional> 

namespace data
{
    template<typename T>
    class Node 
    {
    public:
        virtual ~Node() {}
        virtual const T& get_value() const = 0;
    };

    template<typename T>
    class Branch : public Node<T>
    {
    private:
        std::unique_ptr<Node<T>> left_child;
        std::unique_ptr<Node<T>> right_child;
    public:
        Branch(std::unique_ptr<Node<T>> left, std::unique_ptr<Node<T>> right) : left_child(std::move(left)), right_child(std::move(right))
        {

        }

        const Node<T>& get_left_child() const {
            return *left_child;
        }

        const Node<T>& get_right_child() const {
            return *right_child;
        }

        const T& get_value() const override { return NULL; }
    };
    
    template<typename T>
    class Leaf : public Node<T>
    {
    private:
        T data;
    public:
        Leaf(const T& value) : data(value) {}

        const T& get_value() const override { return data; }

    };

    /*
    template<typename IN, typename OUT>
    std::unique_ptr<Node<OUT>> map(const Node<IN>& tree, std::function<OUT(const IN&)> function)
    {
        if (auto leaf = dynamic_cast<const Leaf<IN>*>(&tree)) {
            return std::make_unique<Leaf<OUT>>(function(leaf->value()));
        }
        else if (auto branch = dynamic_cast<const Branch<IN>*>(&tree)) {
            auto new_left_child = map<IN, OUT>(branch->left_child(), function);
            auto new_right_child = map<IN, OUT>(branch->right_child(), function);
            return std::make_unique<Branch<OUT>>(std::move(new_left_child), std::move(new_right_child));
        }
    }*/
}

#endif
