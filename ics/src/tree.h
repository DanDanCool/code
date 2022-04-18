#pragma once

#include "memarena.h"
#include "stack.h"

#include <string.h>
#include <stdint.h>

template<typename T>
struct BinaryTree
{
    using Type = T;

    struct Node
    {
        Handle Parent;
        Handle Child[2];
        Handle Val;
    };

    enum NodeOrder
    {
        NODE_LEFT,
        NODE_RIGHT,
        NODE_CURRENT,
        NODE_UP
    };

    struct Traverser
    {
        Stack<NodeOrder> Stack;
        Handle Node;
    };

    Arena Nodes;
    Arena Data;
    Handle Root;

    BinaryTree()
        : Nodes()
        , Data()
        , Root(UINT32_MAX)
    {

    }

    uint32_t Alloc(const Type& val)
    {
        Handle h;
        Nodes.Alloc(h);

        Node* n = (Node*)Nodes[h];
        n->Parent = UINT32_MAX;
        n->Child[0] = UINT32_MAX;
        n->Child[1] = UINT32_MAX;

        Data.Alloc(n->Val);
        Type* v = (Type*)Data[n->Val];
        *v = val;

        return i;
    }

    void Init(size_t count)
    {
        Nodes.Init(sizeof(Node), count);
        Data.Init(sizeof(Type), count);
    }

    void Shutdown()
    {
        Nodes.Shutdown();
        Data.Shutdown();
    }

    void Add(const Type& val)
    {
        Node* n = nullptr;
        Handle i = Root;
        while (i)
        {
            n = (Node*)Nodes[i];
            Type* t = (Type*)Data[n->Val];

            if (val == *t)
                return;

            int a = val > *t;
            i = n->Child[a];
        }

        if (!n)
        {
            Root = Alloc(val);
        }
        else
        {
            int a = val < *n->Val;
            n->Child[a] = Alloc(val);
        }
    }

    void Remove(const Type& val)
    {
        Node* n = nullptr;
        Handle i = Root;
        while (i)
        {
            n = (Node*)Nodes[i];
            Type* t = (Type*)Data[n->Val];

            if (val == *t)
            {
                Node* c;
                if (!n->Child[1])
                {
                    // n is a leaf node
                    if (!n->Child[0])
                    {
                        Data.Free(n->Val);
                        Nodes.Free(n);
                        return;
                    }

                    c = (Node*)Nodes[n->Child[0]];
                    n->Child[0] = c->Child[0];
                }
                else
                {
                    // hard case, find successor to current node
                    c = (Node*)Nodes[n->Child[1]];
                    i = c->Child[0];

                    while (i)
                    {
                        c = (Node*)Nodes[i];
                        i = c->Child[0];
                    }

                    Node* p = (Node*)Nodes[c->Parent];
                    Type* pval = (Type*)Data[p->Val];
                    Type* cval = (Type*)Data[c->Val];

                    int a = *cval > *pval;
                    p->Child[a] = UINT32_MAX;
                }

                Handle tmp = n->Val;
                n->Val = c->Val;
                Data.Free(tmp);
                Nodes.Free(c);
                return;
            }

            int a = val > *t;
            i = n->Child[a];
        }
    }

    Type* Find(const Type& val)
    {
        uint32_t i = Root;
        while (i)
        {
            Node* n = (Node*)Nodes[i];
            Type* t = (Type*)Data[n->Val];

            if (val == *t)
                return t;

            int a = val > *t;
            i = n->Child[a];
        }

        return nullptr;
    }

    void InorderTraverser(Traverser& t)
    {
        t.Stack.Init(128);
        t.Stack.Push(NODE_UP);
        t.Node = Root;

        Node* n = (Node*)Nodes[t.Node];
        while (n->Child[0])
        {
            t.Stack.Push(NODE_CURRENT);
            t.Node = n->Child[0];
            n = (Node*)Nodes[t.Node];
        }
    }

    Node* Inorder(Traverser& t)
    {
        if (!t.Node)
            return nullptr;

        Node* n = (Node*)Nodes[t.Node];

        if (!n->Child[1])
        {
            t.Node = n->Parent;
            NodeOrder next = t.Stack.Pop();
            Node* p = (Node*)Nodes[t.Node];
            while (next == NODE_UP && t.Stack.Index)
            {
                t.Node = p->Parent;
                next = t.Stack.Pop();
                p = (Node*)Nodes[t.Node];
            }
        }
        else
        {
            t.Stack.Push(NODE_UP);

            t.Node = n->Child[1];
            Node* c = (Node*)Nodes[t.Node];
            while (c->Child[0])
            {
                t.Stack.Push(NODE_CURRENT);
                t.Node = c->Child[0];
                c = (Node*)Nodes[t.Node];
            }
        }

        return n;
    }

    void PreorderTraverser(Traverser& t)
    {
        t.Stack.Init(128);
        t.Stack.Push(NODE_UP);
        t.Node = Root;

        Node* n = (Node*)Nodes[t.Node];
        if (n->Child[0])
            t.Stack.Push(NODE_LEFT);
        else if (n->Child[1])
            t.Stack.Push(NODE_RIGHT);
        else
            t.Stack.Push(NODE_UP);
    }

    Node* Preorder(Traverser& t)
    {
        if (!t.Node)
            return nullptr;

        Node* n = (Node*)Nodes[t.Node];
        NodeOrder next = t.Stack.Pop();
        switch (next)
        {
            case NODE_LEFT:
            {
                next = n->Child[1] ? NODE_RIGHT : NODE_UP;
                t.Stack.Push(next);
                t.Node = n->Child[0];
                break;
            }
            case NODE_RIGHT:
            {
                t.Node = n->Child[1];
                t.Stack.Push(NODE_UP);
                break;
            }
            case NODE_UP:
            {
                t.Node = n->Parent;
                next = t.Stack.Pop();
                Node* p = (Node*)Nodes[t.Node];
                while (next == NODE_UP && t.Stack.Index)
                {
                    next = t.Stack.Pop();
                    t.Node = p->Parent;
                    p = (Node*)Nodes[t.Node];
                }

                if (next == NODE_RIGHT)
                {
                    t.Stack.Push(NODE_UP);
                    t.Node = p->Child[1];
                }

                break;
            }
        }

        Node* c = (Node*)Nodes[t.Node];
        if (c->Child[0])
            t.Stack.Push(NODE_LEFT);
        else if (c->Child[1])
            t.Stack.Push(NODE_RIGHT);
        else
            t.Stack.Push(NODE_UP);

        return n;
    }

    void PostorderTraverser(Traverser& t)
    {
        t.Stack.Init(128);
        t.Stack.Push(NODE_UP);
        t.Node = Root;

        Node* n = (Node*)Nodes[t.Node];
        while (true)
        {
            if (n->Child[0])
            {
                t.Node = n->Child[0];
                t.Stack.Push(NODE_CURRENT);

                if (n->Child[1])
                    t.Stack.Push(NODE_RIGHT);
            }
            else if (n->Child[1])
            {
                t.Node = n->Child[1];
                t.Stack.Push(NODE_CURRENT);
            }
            else
            {
                break;
            }

            n = (Node*)Nodes[t.Node];
        }
    }

    Node* Postorder(Traverser& t)
    {
        if (!t.Node)
            return nullptr;

        Node* n = (Node*)Nodes[t.Node];

        t.Node = n->Parent;
        Node* c = (Node*)Nodes[t.Node];
        c = (Node*)Nodes[c->Child[1]];

        NodeOrder next = t.Stack.Pop();
        while (next == NODE_RIGHT)
        {
            if (c->Child[0])
            {
                t.Node = c->Child[0];
                t.Stack.Push(NODE_CURRENT);

                if (c->Child[1])
                    t.Stack.Push(NODE_RIGHT);
            }
            else if (c->Child[1])
            {
                t.Node = c->Child[1];
                t.Stack.Push(NODE_CURRENT);
            }
            else
            {
                break;
            }
        }

        return n;
    }
}

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

    enum RBDirection
    {
        LEFT,
        RIGHT
    };

    // TODO: switch from pointers to handles, more cache friendly
    // move Color and Val into Arenas
    struct Node
    {
        Node* Parent;
        Node* Child[2];
        Type Val;
        RBColor Color;
    };

    Arena Data;
    Node* Root;

    RBTree()
        : Data()
        , Root(nullptr)
    {

    }

    void Init(size_t count)
    {
        Data.Init(sizeof(Node), count);
    }

    Node* Find(const Type& val)
    {
        Node* n = Root;
        while (n)
        {
            int a = memcmp(&n->Val, &val, sizeof(Type));

            if (!a)
                break;

            if (a < 0)
                n = n->Child[0];
            else
                n = n->Child[1];
        }

        return n;
    }

    void Rotate(Node* node, int dir)
    {
        Node* child = node->Child[!dir];
        Node* tmp = child->Child[dir];

        child->Parent = node->Parent;
        child->Child[dir] = node;

        tmp->Parent = node;
        node->Child[!dir] = tmp;
    }
};
