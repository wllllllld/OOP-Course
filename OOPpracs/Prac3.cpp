#include <iostream>
#include <queue>
#include <string>
#include <list>
#include <algorithm>

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

	~Student() {}

	friend ostream& operator << (ostream& s, const Student& value);
	friend istream& operator >> (istream& s, Student& value);

	bool lesser(const Student& stud) const
	{
		if (Birthday == stud.Birthday)
		{
			if (Lastname == stud.Lastname)
				return (Firstname > stud.Firstname) ? 1 : 0;
			return (Lastname > stud.Lastname) ? 1 : 0;
		}
		return (Birthday < stud.Birthday) ? 1 : 0;
	}

	bool greater(const Student& stud) const
	{
		if (Birthday == stud.Birthday)
		{
			if (Lastname == stud.Lastname)
				return (Firstname < stud.Firstname) ? 1 : 0;
			return (Lastname < stud.Lastname) ? 1 : 0;
		}
		return (Birthday > stud.Birthday) ? 1 : 0;
	}

	bool operator == (const Student& stud) const
	{
		return Firstname == stud.Firstname &&
			Lastname == stud.Lastname &&
			Birthday == stud.Birthday;
	}

};

bool operator < (const Student& stud, const Student& _stud)
{
	return stud.lesser(_stud);
}

bool operator > (const Student& stud, const Student& _stud)
{
	return stud.greater(_stud);
}

ostream& operator << (ostream& stream, const Student& value)
{
	return stream << value.Firstname << ' ' << value.Lastname << ' ' << value.Address << ' ' << value.Male << ' ' << value.Birthday << ' ' << value.Grade;
}

istream& operator >> (istream& stream, Student& value)
{
	return stream >> value.Firstname >> value.Lastname >> value.Address >> value.Male >> value.Birthday >> value.Grade;
}


template <class T>
class Node
{
private:
	T value;
public:
	T getValue() { return value; }
	void setValue(T v) { value = v; }

	int operator<(Node N)
	{
		return value < N.getValue();
	}

	int operator>(Node N)
	{
		return value > N.getValue();
	}

	void print()
	{
		cout << value;
	}
};


template <class Type, class Container, class Compare>
ostream& operator<<(ostream& out, priority_queue<Type, Container, Compare> q)
{
	out << "\n";
	while (!q.empty())
	{
		out << "  " << q.top() << '\n';
		q.pop();
	}
	out << endl;
	return out;
}

template <class T>
bool BaseLowPriority(T a, T b)
{
	return std::less<T>{}(b, a);
}

template <class T>
bool BaseHighPriority(T a, T b)
{
	return std::less<T>{}(a, b);
}



template <class T>
class Heap
{
private:
	T* arr;
	int size;
	int len;
	bool (*low_priority)(T, T);
	bool (*high_priority)(T, T);
public:
	int getCapacity() { return size; }
	int getCount() { return len; }

	T& operator[](int index)
	{
		return arr[index];
	}

	Heap<T>(int MemorySize = 100, bool(*less)(T a, T b) = BaseLowPriority, bool(*greater)(T a, T b) = BaseHighPriority)
	{
		arr = new T[MemorySize];
		low_priority = less;
		high_priority = greater;
		len = 0;
		size = MemorySize;
	}
	Heap<T>(bool(*less)(T a, T b), bool(*greater)(T a, T b))
	{
		arr = new T[100];
		low_priority = less;
		high_priority = greater;
		len = 0;
		size = 100;
	}
	Heap<T>(const Heap<T>& other)
	{
		arr = new T[other.size];
		size = other.size;
		for (int i = 0; i < size; i++)
			arr[i] = other.arr[i];
		low_priority = other.low_priority;;
		high_priority = other.high_priority;;
		len = other.len;
	}

	void Swap(int index1, int index2)
	{
		T temp;
		temp = arr[index1];
		arr[index1] = arr[index2];
		arr[index2] = temp;
	}

	int GetLeftChildIndex(int index)
	{
		return index * 2 + 1;
	}

	int GetRightChildIndex(int index)
	{
		return index * 2 + 2;
	}

	int GetParentIndex(int index)
	{
		if (index % 2 == 0)
			return index / 2 - 1;
		return index / 2;
	}

	void Heapify(int index = 0)
	{
		int leftChild = 2 * index + 1;;
		int rightChild = 2 * index + 2;
		if (len <= leftChild) return;

		int largestChild = index;
		if (high_priority(arr[leftChild], arr[largestChild]))
			largestChild = leftChild;
		if (rightChild < len && high_priority(arr[rightChild], arr[largestChild]))
			largestChild = rightChild;

		if (largestChild != index)
		{
			Swap(index, largestChild);
			Heapify(largestChild);
		}
	}

	void SiftUp(int index = -1)
	{
		if (index == -1) index = len - 1;
		if (index == 0) return;
		int parent_index = GetParentIndex(index);
		if (high_priority(arr[index], arr[parent_index]))
		{
			Swap(index, parent_index);
			SiftUp(parent_index);
		}
	}

	void push(T v)
	{
		Node<T>* N = new Node<T>;
		N->setValue(v);
		push(N);
	}

	void push(Node<T>* N)
	{
		if (len < size)
		{
			arr[len] = N->getValue();
			len++;
			SiftUp();
		}
	}

	T ExtractMax()
	{
		T res = arr[0];
		Swap(0, len - 1);
		len--;
		if (len > 1)
			Heapify();
		return res;
	}

	T remove(int index)
	{
		T ans = arr[index];
		if (index == len - 1)
			len--;
		else
		{
			Swap(index, len - 1);
			len--;
			if (low_priority(arr[GetParentIndex(index)], arr[index]))
				SiftUp(index);
			else if (high_priority(arr[GetParentIndex(index)], arr[index]))
				Heapify(index);
		}
		return ans;
	}

	template <class T1> friend ostream& operator<< (ostream& stream, Heap<T1> heap);

	~Heap()
	{
		if (arr != NULL)
			delete[] arr;
		len = 0;
		arr = NULL;
	}
};


template <class T>
ostream& operator<< (ostream& out, Heap<T> heap)
{
	out << "\n";
	while (heap.getCount())
		out << "  " << heap.ExtractMax() << "\n";
	out << endl;
	return out;
}


template <class T>
class FibonacciHeap;

template <class T>
class FibNode {
private:
	typename list<FibNode<T>*>::iterator self;
	typename list<FibNode<T>*>::iterator parent;
	list<FibNode<T>*> children;
	T priority;
	int degree;
public:
	friend class FibonacciHeap<T>;
	typename list<FibNode<T>*>::iterator getSelf() { return self; }
	typename list<FibNode<T>*>::iterator getParent() { return parent; }
	list<FibNode<T>*> getChildren() { return children; }
	T getpriority() { return priority; }

	bool hasChildren() { return !children.empty(); }
	bool hasParent() { return parent != children.end(); }
};

template <class T> class FibonacciHeap
{
protected:
	list<FibNode<T>*> heap;
	typename list<FibNode<T>*>::iterator max;
	bool (*low_priority)(T, T);
	bool (*high_priority)(T, T);
public:

	FibonacciHeap<T>(bool(*less)(T, T) = BaseLowPriority, bool (*greater)(T, T) = BaseHighPriority)
	{
		heap.clear();
		max = heap.end();
		low_priority = less;
		high_priority = greater;
	}

	virtual ~FibonacciHeap()
	{
		if (!heap.empty())
		{
			for (typename list<FibNode<T>*>::iterator it = heap.begin(); it != heap.end(); ++it)
				delete* it;
			heap.clear();
		}
	}

	FibNode<T>* push(T priority)
	{
		FibNode<T>* ret = new FibNode<T>;
		ret->priority = priority;
		ret->degree = 0;
		ret->children.clear();
		ret->parent = ret->children.end();
		ret->self = heap.insert(heap.end(), ret);
		if (heap.size() == 1 || high_priority(ret->priority, (*max)->priority))
			max = ret->self;
		return ret;
	}

	void merge(FibonacciHeap& other)
	{
		heap.splice(heap.end(), other.heap);
		if (greater_priority((*other.max)->priority, (*max)->priority))
			max = other.max;
	}

	bool isEmpty()
	{
		return heap.empty();
	}

	T getMax()
	{
		return (*max)->priority;
	}

	T ExtractMax()
	{
		FibNode<T>* maxNode = *max;
		T maxPriority = maxNode->priority;

		if (!maxNode->children.empty())
			heap.splice(heap.end(), maxNode->children);

		heap.erase(maxNode->self);
		delete maxNode;

		if (!heap.empty())
			consolidate();
		else
			max = heap.end();

		return maxPriority;
	}

	void consolidate()
	{
		vector<FibNode<T>*> A(heap.size(), nullptr);
		for (typename list<FibNode<T>*>::iterator it = heap.begin(); it != heap.end(); ++it)
		{
			FibNode<T>* x = *it;
			int d = x->degree;
			while (A[d] != nullptr)
			{
				FibNode<T>* y = A[d];
				if (low_priority(x->priority, y->priority))
					swap(x, y);
				childLink(x, y);
				A[d] = nullptr;
				d++;
			}
			A[d] = x;
		}

		heap.clear();
		max = heap.end();
		for (int i = 0; i < A.size(); i++)
		{
			if (A[i] != nullptr)
			{
				A[i]->self = heap.insert(heap.end(), A[i]);
				if (max == heap.end() || high_priority(A[i]->priority, (*max)->priority))
					max = A[i]->self;
			}
		}
	}

	void childLink(FibNode<T>* parent, FibNode<T>* child)
	{
		parent->children.push_back(child);
		if (!child->children.empty())
			parent->children.splice(parent->children.end(), child->children);
		parent->degree += child->degree;
		child->children.clear();
		parent->degree++;
	}

	void printWithExtractMax()
	{
		cout << "\n";
		int sz = heap.size();
		for (int i = 0; i < sz; i++)
		{
			cout << "  " << ExtractMax() << "\n";
		}
		cout << endl;
	}
};

template<typename T>
void print_queue(T& q)
{
	while (!q.empty())
	{
		cout << q.top() << " ";
		q.pop();
		cout << '\n';
	}

	cout << '\n';
}

int main(int argc, char* argv[])
{

	priority_queue<Student> pqueue_stud;
	pqueue_stud.push(Student("Sidorov", "Sidorov", "Moscow", true, 2007, 8));
	pqueue_stud.push(Student("Petrov", "Petrov", "Moscow", true, 2005, 6));
	pqueue_stud.push(Student("Ivanov", "Ivanov", "Moscow", true, 2004, 5));
	pqueue_stud.push(Student("Sokolov", "Sokolov", "Tver", true, 2004, 4));
	pqueue_stud.push(Student("Sklifosovski", "Sklefasovski", "Saint-Peterburg", true, 2004, 3));

	print_queue(pqueue_stud);


	Heap<Student> heap_stud;

	heap_stud.push(Student("Sidorov", "Sidorov", "Moscow", true, 2007, 8));
	heap_stud.push(Student("Petrov", "Petrov", "Moscow", true, 2005, 6));
	heap_stud.push(Student("Ivanov", "Ivanov", "Moscow", true, 2004, 5));
	heap_stud.push(Student("Sokolov", "Sokolov", "Tver", true, 2004, 4));
	heap_stud.push(Student("Sklifosovski", "Sklefasovski", "Saint-Peterburg", true, 2004, 3));

	heap_stud.remove(3);

	cout << "\n" << heap_stud.ExtractMax();

	FibonacciHeap<Student> fibheap_stud;

	fibheap_stud.push(Student("Sidorov", "Sidorov", "Moscow", true, 2007, 8));
	fibheap_stud.push(Student("Petrov", "Petrov", "Moscow", true, 2005, 6));
	fibheap_stud.push(Student("Ivanov", "Ivanov", "Moscow", true, 2004, 5));
	fibheap_stud.push(Student("Sokolov", "Sokolov", "Tver", true, 2004, 4));
	fibheap_stud.push(Student("Sklifosovski", "Sklefasovski", "Saint-Peterburg", true, 2004, 3));

	cout << "\n" << fibheap_stud.ExtractMax() << fibheap_stud.ExtractMax();

	return 0;
}