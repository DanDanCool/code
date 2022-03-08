#pragma once

#include "memarena.h"

template<typename T>
struct AVLTree;

template<typename T>
using BinaryTree = AVLTree<T>;

template<typename T>
struct AVLTree
{
    using Type = T;

    AVLTree()
    {

    }
};

template<typename T>
struct RBTree
{
    using Type = T;

    enum RBColor
    {
        BLACK,
        RED
    };

    struct Node
    {
        Node* Parent;
        Node* Child[2];
        Type Val;
        RBColor Color;
    };

    MemoryArena Memory;
    Node* Root;

    const int LEFT = 0;
    const int RIGHT = 1;

    RBTree()
        : Memory()
        , Root(nullptr)
    {

    }

    void Init(size_t count)
    {
        Memory.Init(sizeof(Node), count);
    }

private:
    void Rotate(Node* node, int dir)
    {
        Node* child = node->Child[dir];
    }
};
