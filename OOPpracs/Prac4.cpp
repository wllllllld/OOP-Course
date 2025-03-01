#include <iostream>
#include <cmath>

using namespace std;

class Treap
{
public:

    struct Node
    {
    public:
        int m_key, m_priority;

        Node* m_left, * m_right, * m_parent;

        Node(int k, int p)
        {
            m_key = k;
            m_priority = p;
            m_left = m_right = m_parent = nullptr;
        }

        Node(int k)
        {
            m_key = k;
            m_priority = rand();
            m_left = m_right = m_parent = nullptr;
        }

        Node()
        {
            m_left = m_right = m_parent = nullptr;
        }

        Node* getMinimum() const
        {
            if (m_left != nullptr)
                return m_left->getMinimum();

            return (Node*)this;
        }

        Node* getSuccessor() const
        {
            if (m_right != nullptr)
                return m_right->getMinimum();

            Node* current = m_parent;

            while (current != nullptr && current->m_key < m_key)
                current = current->m_parent;

            return current;
        }

        friend ostream& operator<<(ostream& stream, const Node& node)
        {
            stream << node.m_key << "; " << node.m_priority << "\n";

            if (node.m_left)
                stream << *node.m_left;

            if (node.m_right)
                stream << *node.m_right;

            return stream;
        }
    };

    class Iterator : public iterator<input_iterator_tag, int>
    {
    private:
        Node* m_node;

    public:
        Iterator() { m_node = nullptr; }
        Iterator(Node* p) { m_node = p; }
        Iterator(const Iterator& it) { m_node = it.m_node; }

        Iterator& operator=(const Iterator& it)
        {
            m_node = it.m_node;
            return *this;
        }

        Iterator& operator=(Node* p)
        {
            m_node = p;
            return *this;
        }

        bool operator!=(Iterator const& other) const { return m_node != other.m_node; }
        bool operator==(Iterator const& other) const { return m_node == other.m_node; }

        Node* getNode() const { return m_node; }
        void setNode(Node* node) { m_node = node; }

        int& operator*()
        {
            if (m_node == nullptr)
                throw runtime_error("Invalid pointer");

            return m_node->m_priority;
        }

        const int& operator*() const
        {
            if (m_node == nullptr)
                throw runtime_error("Invalid pointer");

            return m_node->m_priority;
        }

        Iterator& operator++()
        {
            m_node = m_node->getSuccessor();
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator it(*this);
            m_node = m_node->getSuccessor();
            return it;
        }
    };

protected:

    Node* m_root;

    virtual Node* merge(Node* left, Node* right)
    {

        if (left->m_priority > right->m_priority)
        {
            if (left->m_right)
                left->m_right = merge(left->m_right, right);
            else
                left->m_right = right;
        }
        else
        {
            if (right->m_left)
                right->m_left = merge(left, right->m_left);
            else
                right->m_left = left;

            left = right;
        }

        return left;
    }

    virtual Node* split(Node* Current, int x, Treap& left, Treap& right)
    {
        if (m_root == nullptr || Current == nullptr)
            return nullptr;

        if (Current->m_key == x)
        {
            Node* Res = Current;
            left.merge(Current->m_left);
            right.merge(Current->m_right);
            Res->m_left = nullptr;
            Res->m_right = nullptr;

            return Res;
        }

        if (Current->m_key < x)
        {
            left.merge(Current->m_left);
            left.merge(Current->m_key, Current->m_priority);

            return split(Current->m_right, x, left, right);
        }
        else
        {
            right.merge(Current->m_right);
            right.merge(Current->m_key, Current->m_priority);

            return split(Current->m_left, x, left, right);
        }
    }


    virtual void merge(Node* node)
    {
        if (m_root == nullptr)
        {
            m_root = node;
            return;
        }
        if (node == nullptr)
            return;

        if (m_root->m_priority > node->m_priority)
        {
            if (m_root->m_right != nullptr)
                m_root->m_right = merge(m_root->m_right, node);
            else
                m_root->m_right = node;
        }
        else
        {
            if (node->m_left != nullptr)
                node->m_left = merge(m_root, node->m_left);
            else
                node->m_left = m_root;
            m_root = node;
        }
    }

public:

    Node* getRoot() const { return m_root; }


    Treap(Node* root = nullptr) { m_root = root; }

    void preOrder(Node* node, void (*func)(Node*))
    {
        if (node)
            func(node);

        if (node && node->m_left)
            preOrder(node->m_left, func);

        if (node && node->m_right)
            preOrder(node->m_right, func);
    }

    virtual void merge(int key, int priority)
    {
        merge(new Node(key, priority));
    }

    virtual void merge(Treap& tree)
    {
        merge(tree.m_root);
    }


    virtual Iterator split(int x, Treap& left, Treap& right)
    {
        return Iterator(split(m_root, x, left, right));
    }

    Iterator begin()
    {
        return Iterator(m_root->getMinimum());
    }

    Iterator end()
    {
        return Iterator(nullptr);
    }

    friend ostream& operator<<(ostream& stream, const Treap& tree)
    {
        if (tree.m_root)
            stream << *tree.m_root;

        return stream;
    }
};


class ImplictTreap : protected Treap
{
public:
    using Treap::Iterator;
    using Treap::Node;

protected:
    Node* merge(Node* left, Node* right)
    {
        if (!left || !right)
            return (left) ? left : right;

        if (left->m_priority > right->m_priority)
        {
            Node* tmp = merge(left->m_right, right);

            if (tmp != nullptr)
                tmp->m_parent = left;

            left->m_right = tmp;

            return left;
        }
        else
        {
            Node* tmp = merge(left, right->m_left);

            if (tmp != nullptr)
                tmp->m_parent = right;

            right->m_left = tmp;

            return right;
        }
    }

    void merge(Node* node)
    {
        Treap::merge(node);
    }


    Node* split(Node* current, int x, ImplictTreap& left, ImplictTreap& right)
    {
        if (m_root == nullptr || current == nullptr)
            return nullptr;

        int leftSize = getSize(current->m_left);

        if (leftSize >= x)
        {
            right.m_root = current;
            right.m_root->m_left = nullptr;

            if (current->m_left)
                left.m_root = split(current->m_left, x, left, right);
            else
                left.m_root = nullptr;

            right.m_root->m_parent = nullptr;
            return left.m_root;
        }
        else
        {
            left.m_root = current;
            left.m_root->m_right = nullptr;

            if (current->m_right)
                right.m_root = split(current->m_right, x - leftSize - 1, left, right);
            else
                right.m_root = nullptr;

            left.m_root->m_parent = nullptr;
            return right.m_root;
        }
    }


    Node* getMinimumOnSegment(Node* node, int start, int end)
    {
        if (!node)
            return nullptr;

        if (!node->m_left)
            return node;

        int leftSize = getSize(node->m_left);

        if (start == leftSize && end == leftSize)
            return node;

        if (start < leftSize)
            return getMinimumOnSegment(node->m_left, start, std::min(end, leftSize - 1));
        else
            return getMinimumOnSegment(node->m_right, start - leftSize - 1, end - leftSize - 1);
    }

    int getSize(Node* node) const
    {
        if (!node)
            return 0;

        return 1 + getSize(node->m_left) + getSize(node->m_right);
    }

public:
    int getSize() const
    {
        return getSize(m_root);
    }

    int getSize(Iterator it) const
    {
        return getSize(it.getNode());
    }

    Iterator getMinimumOnSegment(int start, int end)
    {
        return Iterator(getMinimumOnSegment(m_root, start, end));
    }

    Node* getRoot() const { return Treap::getRoot(); }

    void merge(int key, int priority)
    {
        Treap::merge(key, priority);
    }

    void merge(ImplictTreap& tree)
    {
        Treap::merge(tree);
    }

    Iterator split(int x, ImplictTreap& left, ImplictTreap& right)
    {
        return Treap::split(x, left, right);
    }

    Iterator begin()
    {
        return Treap::begin();
    }

    Iterator end()
    {
        return Treap::end();
    }

    friend ostream& operator<<(ostream& stream, const ImplictTreap& tree)
    {
        if (tree.m_root)
            stream << *tree.m_root;

        return stream;
    }
};

void print(Treap::Node* node)
{
    cout << '(' << node->m_key << ": " << node->m_priority << ')';
}

int main()
{
    srand(time(nullptr));

    Treap tree;


    for (int i = 0; i < 15; i++)
        tree.merge(i, static_cast<int>(100 * sin(15 * double(i))));

    cout << tree;

    Treap tree1, tree2;
    Treap::Iterator it = tree.split(5, tree1, tree2);

    cout << "\n---\n" << tree1 << "\n---\n" << tree2;

    if (it != tree.end())
        cout << "\nNode: " << *it << endl;

    ImplictTreap treap;

    treap.merge(1, 5);
    treap.merge(2, 2);
    treap.merge(3, 8);
    treap.merge(4, 1);
    treap.merge(5, 7);
    treap.merge(6, 3);

    std::cout << "Original Treap:\n"
        << treap << std::endl;

    ImplictTreap::Iterator minElement = treap.getMinimumOnSegment(2, 5);

    cout << "Minimum at [2;5]: " << *minElement << endl;

    return 0;
}