#include <iostream>
#include <memory>
#include <cassert>

template < typename T > struct Node
{

    Node(T field): m_field(field){}

    T m_field;

    std::shared_ptr < Node > left = nullptr;
    std::shared_ptr < Node > right = nullptr;

    std::weak_ptr < Node > parent;

};


int main()
{

    std::shared_ptr < Node<int> > tree = std::make_shared< Node<int> >(2);

    tree->left = std::make_shared< Node<int> >(3);
    tree->left->parent = tree;

    tree->right = std::make_shared< Node<int> >(1);
    tree->right->parent = tree;

    tree->right->right = std::make_shared< Node<int> >(4);
    tree->right->right->parent = tree->right;

    tree->right->right.reset();

    assert(tree->right->right->parent.expired());

}
