#include<iostream>
#include <vector>
#include <math.h>

using namespace std;


class Student
{
public:
	string Firstname, Lastname, Address;
	bool Male;
	int Birthday, Grade;

	Student()
	{
		Male = 0;
		Birthday = 0;
		Grade = 0;
	}

	Student(const char* firstname, const char* lastname, const char* address, bool male, int birthday, int grade)
	{
		Firstname = firstname;
		Lastname = lastname;
		Address = address;
		Male = male;
		Birthday = birthday;
		Grade = grade;
	}

	Student(const Student& stud)
	{
		Firstname = stud.Firstname;
		Lastname = stud.Lastname;
		Address = stud.Address;
		Male = stud.Male;
		Birthday = stud.Birthday;
		Grade = stud.Grade;
	}

	~Student() { }

	friend ostream& operator << (ostream& s, const Student& value);
	friend istream& operator >> (istream& s, Student& value);

	bool operator < (const Student& stud) const
	{
		if (Birthday < stud.Birthday)
			return true;

		if (Lastname < stud.Lastname)
			return true;

		if (Firstname < stud.Firstname)
			return true;

		return false;
	}

	bool operator > (const Student& stud) const
	{
		if (Birthday > stud.Birthday)
			return true;

		if (Lastname > stud.Lastname)
			return true;

		if (Firstname > stud.Firstname)
			return true;

		return false;
	}

	bool operator == (const Student& stud) const
	{
		return Firstname == stud.Firstname &&
			Lastname == stud.Lastname &&
			Birthday == stud.Birthday;
	}
};

ostream& operator << (ostream& stream, const Student& value)
{
	return stream << value.Firstname << ' ' << value.Lastname << ' ' << value.Address << ' ' << value.Male << ' ' << value.Birthday << ' ' << value.Grade;
}

istream& operator >> (istream& stream, Student& value)
{
	return stream >> value.Firstname >> value.Lastname >> value.Address >> value.Male >> value.Birthday >> value.Grade;
}

template<class KeyType, class ValueType>
class Node
{
protected:
	KeyType key;
	ValueType value;
	Node* parent;
	Node* left;
	Node* right;
	int height;
public:
	virtual void setKey(KeyType key) { this->key = key; }
	virtual void setValue(ValueType value) { this->value = value; }
	virtual void setLeft(Node* N) { left = N; }
	virtual void setRight(Node* N) { right = N; }
	virtual void setParent(Node* N) { parent = N; }
	virtual void setHeight(int height) { this->height = height; }

	KeyType getKey() const { return key; }
	ValueType getValue() const { return value; }
	int getHeight() const { return height; }
	virtual Node* getLeft() const { return left; }
	virtual Node* getRight() const { return right; }
	virtual Node* getParent() const { return parent; }

	Node<KeyType, ValueType>(const Node<KeyType, ValueType>& node) : key(node.key), value(node.value), left(node.left), right(node.right), parent(node.parent), height(node.height) {}

	Node<KeyType, ValueType>(KeyType key, ValueType value)
	{
		this->key = key; this->value = value;
		left = right = parent = NULL;
		height = 1;
	}

	Node<KeyType, ValueType>()
	{
		key = KeyType(); value = ValueType();
		left = right = parent = NULL;
		height = 1;
	}

	Node<KeyType, ValueType>* successor()
	{
		Node<KeyType, ValueType>* res;

		if (right != NULL) {
			res = right;
			for (; res->getLeft() != NULL; res = res->getLeft());
			return res;
		}

		res = parent;

		for (Node<KeyType, ValueType>* current = this; current != NULL && res != NULL; res = res->getParent(), current = current->getParent())
			if (res->getLeft() == current) return res;

		return this;
	}

	Node<KeyType, ValueType>* predecesor()
	{
		Node<KeyType, ValueType>* res;

		if (left != NULL) {
			res = left;
			for (; res->getRight() != NULL; res = res->getRight());
			return res;
		}

		res = parent;

		for (Node<KeyType, ValueType>* current = this; res != NULL; res = res->getParent(), current = current->getParent())
			if (res->getRight() == current) return res;

		return this;
	}

	void swap(Node<KeyType, ValueType>& node)
	{
		std::swap(key, node.key);
		std::swap(value, node.value);
	}

	template<class KeyType1, class  ValueType1>
	friend ostream& operator<<(ostream& s, Node<KeyType1, ValueType1>& N);

	template<class KeyType, class  ValueType>
	friend ostream& operator<<(ostream& stream, Node<KeyType, vector<ValueType>*>& N);
};

template<class KeyType, class ValueType>
ostream& operator<< (ostream& s, Node<KeyType, ValueType>& N)
{
	s << "Key: " << N.key << " Value: " << N.value << "\n";
	return s;
}

template<class KeyType, class ValueType>
ostream& operator<< (ostream& s, Node<KeyType, vector<ValueType>*>& N)
{
	s << "Key: " << N.key << " Value: " << *N.value << "\n";
	return s;
}

template <class KeyType, class ValueType>
void print(Node < KeyType, ValueType>* node)
{
	cout << *node << "\n";
}

template<typename KeyType, typename ValueType>
class TreeIterator : public std::iterator<std::input_iterator_tag, KeyType, ValueType>
{
private:
	Node<KeyType, ValueType>* ptr;
public:

	TreeIterator() { ptr = NULL; }
	TreeIterator(Node<KeyType, ValueType>* p) { ptr = p; }
	TreeIterator(const TreeIterator& it) { ptr = it.ptr; }

	TreeIterator& operator=(const TreeIterator& it) { ptr = it.ptr; return *this; }
	TreeIterator& operator=(Node<KeyType, ValueType>* p) { ptr = p; return *this; }

	bool operator!=(TreeIterator const& other) const { return ptr != other.ptr; }
	bool operator==(TreeIterator const& other) const { return ptr == other.ptr; }
	Node<KeyType, ValueType>& operator*() { return *ptr; }
	TreeIterator& operator++()
	{
		if (ptr != NULL) ptr = ptr->successor();
		return *this;
	}
	TreeIterator operator++(int v)
	{
		Node<KeyType, ValueType>* p = ptr;
		if (ptr != NULL) ptr = ptr->successor();
		return TreeIterator(p);
	}

	TreeIterator& operator--()
	{
		if (ptr != NULL) ptr = ptr->predecesor();
		return *this;
	}
	TreeIterator operator--(int v)
	{
		Node<KeyType, ValueType>* p = ptr;
		if (ptr != NULL) ptr = ptr->predecesor();
		return TreeIterator(p);
	}
};

template <class KeyType, class ValueType>
class Tree
{
protected:

	Node<KeyType, ValueType>* root;

	virtual Node<KeyType, ValueType>* Add_R(Node<KeyType, ValueType>* N, Node<KeyType, ValueType>* current)
	{
		if (N == NULL) return NULL;

		if (root == NULL) return root = N;

		if (current->getKey() > N->getKey())
		{
			if (current->getLeft() != NULL)
				current->setLeft(Add_R(N, current->getLeft()));
			else
				current->setLeft(N);
			current->getLeft()->setParent(current);
		}
		if (current->getKey() < N->getKey())
		{
			if (current->getRight() != NULL)
				current->setRight(Add_R(N, current->getRight()));
			else
				current->setRight(N);
			current->getRight()->setParent(current);
		}

		if (current->getKey() == N->getKey())
		{
			swap(current, N);
		}

		return current;
	}

	virtual Node<KeyType, ValueType>* Find(KeyType key, Node<KeyType, ValueType>* current)
	{
		if (current == NULL) return NULL;
		if (current->getKey() == key)
			return current;
		if (current->getKey() > key)
			return Find(key, current->getLeft());
		else
			return Find(key, current->getRight());
	}


public:

	Tree() { root = NULL; }

	virtual Node<KeyType, ValueType>* GetRoot()const { return root; }

	virtual Node<KeyType, ValueType>* Add_R(Node<KeyType, ValueType>* N)
	{
		return Add_R(N, root);
	}

	virtual Node<KeyType, ValueType>* Add(KeyType key, ValueType value)
	{
		Node<KeyType, ValueType>* newelem = new Node<KeyType, ValueType>;
		newelem->setKey(key);
		newelem->setValue(value);
		return Add_R(newelem);
	}

	virtual Node<KeyType, ValueType>* Add(KeyType key)
	{
		Node<KeyType, ValueType>* newelem = new Node<KeyType, ValueType>;
		newelem->setKey(key);
		return Add_R(newelem);
	}

	virtual Node<KeyType, ValueType>* Remove(Node<KeyType, ValueType>* node)
	{
		Node<KeyType, ValueType>* nextelem;

		while (node->getLeft() != NULL && node->getRight() != NULL)
		{
			nextelem = node->successor();
			node->swap(*nextelem);
			node = nextelem;
		}

		nextelem = node;

		if (node->getRight() == NULL && node->getLeft() == NULL)
			nextelem = NULL;

		if (node->getRight() != NULL)
			nextelem = node->getRight();

		if (node->getLeft() != NULL)
			nextelem = node->getLeft();

		if (root == node) root = nextelem;
		else
			if (node->getParent()->getRight() == node)
				node->getParent()->setRight(nextelem);
			else
				node->getParent()->setLeft(nextelem);

		if (nextelem != NULL) nextelem->setParent(node->getParent());

		return node;
	}

	virtual Node<KeyType, ValueType>* Remove(TreeIterator<KeyType, ValueType>& it)
	{
		return Remove(&(*it));
	}

	virtual Node<KeyType, ValueType>* Min(Node<KeyType, ValueType>* Current = NULL) const
	{
		if (root == NULL) return NULL;

		if (Current == NULL) Current = root;

		for (; Current->getLeft() != NULL; Current = Current->getLeft());

		return Current;
	}
	virtual Node<KeyType, ValueType>* Max(Node<KeyType, ValueType>* Current = NULL) const
	{

		if (root == NULL) return NULL;

		if (Current == NULL) Current = root;

		for (; Current->getRight() != NULL; Current = Current->getRight());

		return Current;
	}

	TreeIterator<KeyType, ValueType> begin() const { return TreeIterator<KeyType, ValueType>(Min()); }
	TreeIterator<KeyType, ValueType> end() const { return TreeIterator<KeyType, ValueType>(Max()); }

	virtual void InOrder(Node<KeyType, ValueType>* N, void(*f)(Node<KeyType, ValueType>*)) const
	{
		if (N != NULL && N->getLeft() != NULL)
			InOrder(N->getLeft(), f);
		if (N != NULL)
			f(N);
		if (N != NULL && N->getRight() != NULL)
			InOrder(N->getRight(), f);
	}

	virtual void InOrder(TreeIterator<KeyType, ValueType> it, void(*f)(Node<KeyType, ValueType>*)) const
	{
		for (; it != end(); ++it)
			f(&*it);
		f(&*it);
	}

	virtual void PostOrder(Node<KeyType, ValueType>* N, void(*f)(Node<KeyType, ValueType>*)) const
	{
		if (N != NULL && N->getLeft() != NULL)
			PostOrder(N->getLeft(), f);
		if (N != NULL && N->getRight() != NULL)
			PostOrder(N->getRight(), f);
		if (N != NULL)
			f(N);
	}

	virtual void PostOrder(TreeIterator<KeyType, ValueType> it, void(*f)(Node<KeyType, ValueType>*)) const
	{
		for (; it != begin(); --it)
			f(&*it);
		f(&*it);
	}
};

template <class KeyType, class ValueType>
class AVLTree : public Tree<KeyType, ValueType>
{
	using Tree<KeyType, ValueType>::root;
protected:
	int bfactor(Node<KeyType, ValueType>* p) const
	{
		int heightleft = 0;
		int heightright = 0;
		if (p->getLeft() != NULL)
			heightleft = p->getLeft()->getHeight();
		if (p->getRight() != NULL)
			heightright = p->getRight()->getHeight();
		return (heightright - heightleft);
	}

	void fixHeight(Node<KeyType, ValueType>* p)
	{
		int heightleft = 0;
		int heightright = 0;
		if (p->getLeft() != NULL)
			heightleft = p->getLeft()->getHeight();
		if (p->getRight() != NULL)
			heightright = p->getRight()->getHeight();
		p->setHeight((heightleft > heightright ? heightleft : heightright) + 1);
	}

	Node<KeyType, ValueType>* RotateRight(Node<KeyType, ValueType>* p)
	{

		Node<KeyType, ValueType>* q = p->getLeft();

		if (p == root) root = q;
		else
			if (p->getParent()->getRight() == p)
				p->getParent()->setRight(q);
			else
				p->getParent()->setLeft(q);

		q->setParent(p->getParent());
		p->setParent(q);

		p->setLeft(q->getRight());
		if (q->getRight() != NULL) q->getRight()->setParent(p);
		q->setRight(p);

		fixHeight(p);
		fixHeight(q);

		return q;
	}

	Node<KeyType, ValueType>* RotateLeft(Node<KeyType, ValueType>* q)
	{

		Node<KeyType, ValueType>* p = q->getRight();

		if (root == q) root = p;
		else
			if (q->getParent()->getRight() == q)
				q->getParent()->setRight(p);
			else
				q->getParent()->setLeft(p);

		p->setParent(q->getParent());
		q->setParent(p);

		q->setRight(p->getLeft());
		if (p->getLeft() != NULL) p->getLeft()->setParent(q);
		p->setLeft(q);

		fixHeight(q);
		fixHeight(p);

		return p;
	}

	Node<KeyType, ValueType>* Balance(Node<KeyType, ValueType>* node)
	{

		fixHeight(node);

		if (bfactor(node) == 2)
		{
			if (bfactor(node->getRight()) < 0) RotateRight(node->getRight());
			return RotateLeft(node);
		}

		if (bfactor(node) == -2)
		{
			if (bfactor(node->getLeft()) > 0)  RotateLeft(node->getLeft());
			return RotateRight(node);
		}

		return node;
	}

	virtual Node<KeyType, ValueType>* Add_R(Node<KeyType, ValueType>* N, Node<KeyType, ValueType>* current)
	{
		N = Tree<KeyType, ValueType>::Add_R(N, current);
		if (current != NULL)
			return Balance(current);
		return N;
	}

public:

	AVLTree() : Tree<KeyType, ValueType>() {}

	virtual Node<KeyType, ValueType>* Add_R(Node<KeyType, ValueType>* N)
	{
		N = Add_R(N, root);
		return N;
	}

	virtual Node<KeyType, ValueType>* Add(KeyType key, ValueType value)
	{
		Node<KeyType, ValueType>* newelem = new Node<KeyType, ValueType>;
		newelem->setKey(key);
		newelem->setValue(value);
		return Add_R(newelem);
	}

	virtual Node<KeyType, ValueType>* Add(KeyType key)
	{
		Node<KeyType, ValueType>* newelem = new Node<KeyType, ValueType>;
		newelem->setKey(key);
		return Add_R(newelem);
	}

	virtual Node<KeyType, ValueType>* Remove(Node<KeyType, ValueType>* node)
	{
		Node<KeyType, ValueType>* n = Tree<KeyType, ValueType>::Remove(node);
		Node<KeyType, ValueType>* nnode = n->getParent();
		while (nnode != NULL)
		{
			Balance(nnode);
			nnode = nnode->getParent();
		}
		return n;
	}

	virtual Node<KeyType, ValueType>* Remove(TreeIterator<KeyType, ValueType>& it)
	{
		return Remove(&(*it));
	}

	virtual void InOrder(Node<KeyType, ValueType>* N, void(*f)(Node<KeyType, ValueType>*)) const
	{
		Tree<KeyType, ValueType>::InOrder(N, f);
	}

	virtual void InOrder(TreeIterator<KeyType, ValueType> it, void(*f)(Node<KeyType, ValueType>*)) const
	{
		Tree<KeyType, ValueType>::InOrder(it, f);
	}

	virtual void PostOrder(Node<KeyType, ValueType>* N, void(*f)(Node<KeyType, ValueType>*)) const
	{
		Tree<KeyType, ValueType>::PostOrder(N, f);
	}

	virtual void PostOrder(TreeIterator<KeyType, ValueType> it, void(*f)(Node<KeyType, ValueType>*)) const
	{
		Tree<KeyType, ValueType>::PostOrder(it, f);
	}

};

template <class KeyType, class ValueType>
class MultiAVLTree : private AVLTree<KeyType, vector<ValueType>*>
{
	using Tree<KeyType, vector<ValueType>*>::root;
protected:

	virtual Node<KeyType, vector<ValueType>*>* Add_R(Node<KeyType, vector<ValueType>*>* N, Node<KeyType, vector<ValueType>*>* current)
	{
		if (N == NULL) return NULL;

		if (root == NULL) return root = N;

		if (current->getKey() > N->getKey())
		{
			if (current->getLeft() != NULL)
				current->setLeft(Add_R(N, current->getLeft()));
			else
				current->setLeft(N);
			current->getLeft()->setParent(current);
		}
		if (current->getKey() < N->getKey())
		{
			if (current->getRight() != NULL)
				current->setRight(Add_R(N, current->getRight()));
			else
				current->setRight(N);
			current->getRight()->setParent(current);
		}

		if (current->getKey() == N->getKey())
		{
			vector<ValueType>* v = N->getValue();
			for (typename vector<ValueType>::iterator it = v->begin(); it != v->end(); it++)
				current->getValue()->push_back(*it);
		}

		if (current != NULL)
			AVLTree<KeyType, vector<ValueType>*>::Balance(current);
		return current;
	}

public:

	MultiAVLTree() :AVLTree<KeyType, vector<ValueType>*>() {}

	virtual Node<KeyType, vector<ValueType>*>* Add_R(Node<KeyType, vector<ValueType>*>* N)
	{
		N = Add_R(N, root);
	}

	virtual Node<KeyType, vector<ValueType>*>* Add(KeyType key, vector<ValueType>* value)
	{
		Node<KeyType, vector<ValueType>*>* newelem = new Node<KeyType, vector<ValueType>*>*;
		newelem->setKey(key);
		newelem->setValue(value);
		return Add_R(newelem);
	}

	virtual Node<KeyType, vector<ValueType>*>* Add(KeyType key)
	{
		Node<KeyType, vector<ValueType>*>* newelem = new Node<KeyType, vector<ValueType>*>*;
		newelem->setKey(key);
		return Add_R(newelem);
	}

	virtual Node<KeyType, vector<ValueType>*>* Remove(Node<KeyType, vector<ValueType>*>* node)
	{
		return AVLTree<KeyType, vector<ValueType>*>::Remove(node);
	}

	virtual Node<KeyType, vector<ValueType>*>* Remove(TreeIterator<KeyType, vector<ValueType>*>& it)
	{
		return AVLTree<KeyType, vector<ValueType>*>::Remove(&(*it));
	}

	virtual Node<KeyType, vector<ValueType>*>* operator[](KeyType key)
	{
		return Tree<KeyType, vector<ValueType>*>::Find(key);
	}

	virtual void InOrder(Node<KeyType, ValueType>* N, void(*f)(Node<KeyType, ValueType>*)) const
	{
		Tree<KeyType, ValueType>::InOrder(N, f);
	}

	virtual void InOrder(TreeIterator<KeyType, ValueType> it, void(*f)(Node<KeyType, ValueType>*)) const
	{
		Tree<KeyType, ValueType>::InOrder(it, f);
	}

	virtual void PostOrder(Node<KeyType, ValueType>* N, void(*f)(Node<KeyType, ValueType>*)) const
	{
		Tree<KeyType, ValueType>::PostOrder(N, f);
	}

	virtual void PostOrder(TreeIterator<KeyType, ValueType> it, void(*f)(Node<KeyType, ValueType>*)) const
	{
		Tree<KeyType, ValueType>::PostOrder(it, f);
	}
};

template <class KeyType, class ValueType>
class SplayTree : protected AVLTree<KeyType, ValueType>
{
	using Tree<KeyType, ValueType>::root;
protected:

	Node<KeyType, ValueType>* Add_R(Node<KeyType, ValueType>* N, Node<KeyType, ValueType>* current)
	{
		return AVLTree<KeyType, ValueType>::Add_R(N, current);
	}

	Node<KeyType, ValueType>* Splay(Node<KeyType, ValueType>* N)
	{
		while (root != N)
		{
			if (N->getParent()->getRight() == N)
				AVLTree<KeyType, ValueType>::RotateLeft(N->getParent());
			else
				AVLTree<KeyType, ValueType>::RotateRight(N->getParent());
		}
		root = N;
		return root;
	}

public:

	SplayTree() : AVLTree<KeyType, ValueType>() {}

	Node<KeyType, ValueType>* GetRoot()const { return root; }

	Node<KeyType, ValueType>* Add_R(Node<KeyType, ValueType>* N)
	{
		N = Add_R(N, root);
		return N;
	}

	Node<KeyType, ValueType>* Add(KeyType key, ValueType value)
	{
		Node<KeyType, ValueType>* newelem = new Node<KeyType, ValueType>;
		newelem->setKey(key);
		newelem->setValue(value);
		return Add_R(newelem);
	}

	Node<KeyType, ValueType>* Add(KeyType key)
	{
		Node<KeyType, ValueType>* newelem = new Node<KeyType, ValueType>;
		newelem->setKey(key);
		return Add_R(newelem);
	}

	Node<KeyType, ValueType>* Find(Node<KeyType, ValueType>* N)
	{
		return Splay(N);
	}


	Node<KeyType, ValueType>* Find(KeyType key, ValueType value)
	{
		Node<KeyType, ValueType>* newelem = new Node<KeyType, ValueType>;
		newelem->setKey(key);
		newelem->setValue(value);
		return Splay(newelem);
	}

	Node<KeyType, ValueType>* Find(KeyType key)
	{
		return Splay(Tree<KeyType, ValueType>::Find(key, root));
	}

	Node<KeyType, ValueType>* Remove(Node<KeyType, ValueType>* node)
	{
		return Tree<KeyType, ValueType>::Remove(node);
	}

	virtual Node<KeyType, ValueType>* Remove(TreeIterator<KeyType, ValueType>& it)
	{
		return Tree<KeyType, ValueType>::Remove(&(*it));
	}

	virtual void InOrder(Node<KeyType, ValueType>* N, void(*f)(Node<KeyType, ValueType>*)) const
	{
		Tree<KeyType, ValueType>::InOrder(N, f);
	}

	virtual void InOrder(TreeIterator<KeyType, ValueType> it, void(*f)(Node<KeyType, ValueType>*)) const
	{
		Tree<KeyType, ValueType>::InOrder(it, f);
	}

	virtual void PostOrder(Node<KeyType, ValueType>* N, void(*f)(Node<KeyType, ValueType>*)) const
	{
		Tree<KeyType, ValueType>::PostOrder(N, f);
	}

	virtual void PostOrder(TreeIterator<KeyType, ValueType> it, void(*f)(Node<KeyType, ValueType>*)) const
	{
		Tree<KeyType, ValueType>::PostOrder(it, f);
	}
};


int main()
{
	Tree<string, Student> tree;


	tree.Add("Sidorov", Student("Sidorov", "Sidorov", "Novosib", true, 2007, 8));
	tree.Add("Petrov", Student("Petrov", "Petrov", "Moscow", true, 2005, 6));

	SplayTree<string, Student> splay;


	splay.Add("Sidorov", Student("Sidorov", "Sidorov", "Novosib", true, 2007, 8));
	splay.Add("Petrov", Student("Petrov", "Petrov", "Moscow", true, 2005, 6));


	cout << "InOrder:" << "\n";

	splay.InOrder(splay.GetRoot(), print);

	cout << "PostOrder:" << "\n";

	splay.PostOrder(splay.GetRoot(), print);

	cout << "PostOrder:" << "\n";

	splay.PostOrder(splay.GetRoot(), print);
}