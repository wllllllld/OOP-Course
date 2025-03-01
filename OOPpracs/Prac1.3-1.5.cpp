#include <iostream>
#include <fstream>

using namespace std;

template <class T>
class IteratedLinkedList;

template <class T>
class Queue;

template <class T>
class OrderedQueue;

template <class T>
class ListIterator;

class Exception : public exception
{
protected:
	char* str;
public:
	Exception(const char* s)
	{
		str = new char[strlen(s) + 1];
		strcpy_s(str, strlen(s) + 1, s);
	}
	Exception(const Exception& e)
	{
		str = new char[strlen(e.str) + 1];
		strcpy_s(str, strlen(e.str) + 1, e.str);
	}
	~Exception()
	{
		delete[] str;
	}

	virtual void print()
	{
		cout << "Exception: " << str << "; " << what();
	}
};

class IteratorNullException : public Exception
{
public:
	IteratorNullException(const char* s) : Exception(s) {}
	IteratorNullException(const IteratorNullException& c) : Exception(c) {}

	virtual void print()
	{
		cout << str;
	}
};

class Invalidlvlexception : public Exception
{
public:
	Invalidlvlexception(const char* s) : Exception(s) {}
	Invalidlvlexception(const Invalidlvlexception& c) : Exception(c) {}

	virtual void print()
	{
		cout << "Invalidlvlexception: " << str << what();
	}
};

class programmer
{
public:
	string sname;
	string n;
	string mail;
	string s;
	string tg;
	string language;
	string job;
	int lvl;

	programmer()
	{
		sname = "";
		n = "";
		mail = "";
		s = "";
		tg = "";
		language = "";
		job = "";
		lvl = 0;
	}

	programmer(string surname, string name, string email, string skype, string telegram, string mainlanguage, string currentjob, int level)
	{
		if (level > 10 || level < 1)
		{
			throw Invalidlvlexception("level needs to be in[1, 10]");
		}
		sname = surname;
		n = name;
		mail = email;
		s = skype;
		tg = telegram;
		language = mainlanguage;
		job = currentjob;
		lvl = level;
	}

	~programmer() {}

	programmer operator =(programmer p)
	{
		sname = p.sname;
		n = p.n;
		mail = p.mail;
		s = p.s;
		tg = p.tg;
		language = p.language;
		job = p.job;
		lvl = p.lvl;
		return *this;
	}

	bool operator ==(programmer p)
	{
		return (lvl == p.lvl && language == p.language && sname == p.sname && n == p.n) ? 1 : 0;
	}

	bool operator !=(programmer p)
	{
		return (lvl != p.lvl || language != p.language || sname != p.sname || n != p.n) ? 1 : 0;
	}

	bool operator >(programmer p)
	{
		if (lvl == p.lvl)
		{
			if (language == p.language)
			{
				if (sname == p.sname)
					return (n < p.n) ? 1 : 0;
				return (sname < p.sname) ? 1 : 0;
			}
			return(language < p.language) ? 1 : 0;
		}
		return (lvl > p.lvl) ? 1 : 0;
	}

	bool operator <(programmer p)
	{
		if (lvl == p.lvl)
		{
			if (language == p.language)
			{
				if (sname == p.sname)
					return (n > p.n) ? 1 : 0;
				return (sname > p.sname) ? 1 : 0;
			}
			return(language > p.language) ? 1 : 0;
		}
		return (lvl < p.lvl) ? 1 : 0;
	}

	friend ostream& operator<<(ostream& s, programmer p);
};

ostream& operator<<(ostream& s, programmer p)
{
	s << p.lvl << " " << p.language << " " << p.sname << " " << p.n << "\n";
	return s;
}


template <class T>
class Element
{
private:

	Element* next;
	Element* prev;

	T field;
public:

	Element(T value = 0, Element<T>* next_ptr = NULL, Element<T>* prev_ptr = NULL)
	{
		field = value;
		next = next_ptr;
		prev = prev_ptr;
	}

	virtual Element* getNext() { return next; }
	virtual void setNext(Element* value) { next = value; }

	virtual Element* getPrevious() { return prev; }
	virtual void setPrevious(Element* value) { prev = value; }

	virtual T getValue() { return field; }
	virtual void setValue(T value) { field = value; }
	template<class T> friend ostream& operator<< (ostream& ustream, Element<T>& obj);
};

template<class T>
ostream& operator << (ostream& ustream, Element<T>& obj)
{
	ustream << obj.field;
	return ustream;
}

template <class T>
class LinkedListParent
{
protected:

	Element<T>* head;
	Element<T>* tail;

	int num;
public:
	virtual int Number() { return num; }
	virtual Element<T>* getBegin() { return head; }
	virtual Element<T>* getEnd() { return tail; }
	LinkedListParent()
	{
		cout << "\nParent constructor";
		head = NULL;
		tail = NULL;
		num = 0;
	}
	ListIterator<T> begin()
	{
		ListIterator<T> it = head;
		return it;
	}
	ListIterator<T> end()
	{
		ListIterator<T> it = tail;
		return it;
	}

	virtual Element<T>* push(T value) = 0;

	virtual Element<T>* pop() = 0;
	virtual ~LinkedListParent()
	{
		Element<T>* current = head;
		while (current != NULL)
		{
			Element<T>* next = current->getNext();
			delete current;
			current = next;
		}
		head = tail = NULL;
		cout << "\nParent destructor";
	}

	virtual Element<T>* operator[](int i)
	{	
		if (i<0 || i>num) return NULL;
		int k = 0;

		Element<T>* cur = head;
		for (k = 0; k < i; k++)
		{
			cur = cur->getNext();
		}
		return cur;
	}
	template<class T> friend ostream& operator<< (ostream& ustream, LinkedListParent<T>& obj);
	template<class T> friend istream& operator>> (istream& ustream, LinkedListParent<T>& obj);
};

template<class T>
ostream& operator << (ostream& ustream, LinkedListParent<T>& obj)
{
	if (typeid(ustream).name() == typeid(ofstream).name())
	{
		ustream << obj.num << "\n";
		for (Element<T>* current = obj.getBegin(); current != NULL; current = current->getNext())
			ustream << current->getValue() << " ";
		return ustream;
	}
	ustream << "\nLength: " << obj.num << "\n";
	int i = 0;
	for (Element<T>* current = obj.getBegin(); current != NULL; current = current->getNext(), i++)
		ustream << "arr[" << i << "] = " << current->getValue() << "\n";
	return ustream;
}

template<class T>
istream& operator >> (istream& ustream, LinkedListParent<T>& obj)
{
	int len;
	ustream >> len;
	double v = 0;
	for (int i = 0; i < len; i++)
	{
		ustream >> v;
		obj.push(v);
	}
	return ustream;
}

template<typename ValueType>
class ListIterator : public std::iterator<std::input_iterator_tag, ValueType>
{
	friend class IteratedLinkedList<ValueType>;
	friend class Queue<ValueType>;
	friend class OrderedQueue<ValueType>;
private:
public:
	ListIterator() { ptr = NULL; }
	ListIterator(Element<ValueType>* p) { ptr = p; }
	ListIterator(const ListIterator& it) { ptr = it.ptr; }
	bool operator!=(ListIterator const& other) const { return ptr != other.ptr; }
	bool operator==(ListIterator const& other) const { return ptr == other.ptr; }

	Element<ValueType>& operator*()
	{
		if (ptr == NULL)
			throw IteratorNullException("Iterator is pointing to NULL");
		return *ptr;
	}
	ListIterator& operator++()
	{
		if (ptr->getNext() == NULL)
			throw IteratorNullException("Iterator is pointing to NULL");
		ptr = ptr->getNext();
		return *this;
	}
	ListIterator& operator++(int v)
	{
		if (ptr->getNext() == NULL)
			throw IteratorNullException("Iterator is pointing to NULL");
		ptr = ptr->getNext();
		return *this;
	}
	ListIterator& operator--()
	{
		if (ptr->getPrevious() == NULL)
			throw IteratorNullException("Iterator is pointing to NULL");
		ptr = ptr->getPrevious();
		return *this;
	}
	ListIterator& operator--(int v)
	{
		if (ptr->getPrevious() == NULL)
			throw IteratorNullException("Iterator is pointing to NULL");
		ptr = ptr->getPrevious();
		return *this;
	}
	ListIterator& operator=(const ListIterator& it)
	{
		ptr = it.ptr;
		return *this;
	}
	ListIterator& operator=(Element<ValueType>* p)
	{
		ptr = p;
		return *this;
	}
private:
	Element<ValueType>* ptr;
};

template <class T>
class IteratedLinkedList : public LinkedListParent<T>
{
public:
	using LinkedListParent<T>::head;
	using LinkedListParent<T>::tail;
	using LinkedListParent<T>::num;
	IteratedLinkedList() : LinkedListParent<T>()
	{
		cout << "\nIteratedLinkedList constructor";
	}
	virtual ~IteratedLinkedList()
	{
		Element<T>* current = head;
		while (current != NULL)
		{
			Element<T>* next = current->getNext();
			delete current;
			current = next;
		}
		head = tail = NULL;
		cout << "\nIteratedLinkedList destructor";
	}
	ListIterator<T> begin()
	{
		ListIterator<T> it = LinkedListParent<T>::head;
		return it;
	}
	ListIterator<T> end()
	{
		ListIterator<T> it = LinkedListParent<T>::tail;
		return it;
	}
};

template<class T>
class Queue : public IteratedLinkedList<T>
{
public:

	using LinkedListParent<T>::head;
	using LinkedListParent<T>::tail;
	using LinkedListParent<T>::num;

	Queue() : IteratedLinkedList<T>() { cout << "\nQueue cunstructor"; }

	ListIterator<T> begin()
	{
		ListIterator<T> it(head);
		return it;
	}
	ListIterator<T> end()
	{
		ListIterator<T> it(tail);
		return it;
	}

	~Queue()
	{
		Element<T>* current = head;
		while (current != NULL)
		{
			Element<T>* next = current->getNext();
			delete current;
			current = next;
		}
		head = tail = NULL;
		cout << "\nQueue destructor";
	}

	virtual Element<T>* pop()
	{
		if (head == NULL)return NULL;
		Element<T>* res = head;
		if (head == tail)
		{
			head = tail = NULL;
			num = 0;
			return res;
		}
		Element<T>* newhead = head;
		newhead = newhead->getNext();
		newhead->getPrevious()->setNext(NULL);
		newhead->setPrevious(NULL);
		head = newhead;
		num--;
		return res;
	}

	virtual Element<T>* push(T value)
	{
		if (head == NULL)
		{
			head = tail = new Element<T>(value);
			return head;
		}
		Element<T>* newelem = new Element<T>(value);
		newelem->setPrevious(tail);
		newelem->getPrevious()->setNext(newelem);
		tail = newelem;
		return tail;
	}

	Queue<T>& filter(bool (*predicate)(T))
	{
		Queue<T> res;
		for (Element<T>* current = head; current != tail; current = current->getNext())
			if (predicate(current->getValue()))
			{
				res.push(current->getValue());
			}
		return &res;
	}
	template <class T1>
	friend ostream& operator <<(ostream& s, Queue<T1>& q);
};

template <class T1>
ostream& operator <<(ostream& s, Queue<T1>& q)
{
	auto it = q.begin();
	while (it != q.end())
	{
		cout << *it << " ";
		it++;
	}
	cout << *it << " ";
	return s;
}

template <class T>
class OrderedQueue : public Queue<T>
{
public:

	using LinkedListParent<T>::head;
	using LinkedListParent<T>::tail;
	using LinkedListParent<T>::num;

	OrderedQueue() : Queue<T>() { cout << "\nOrderedQueue constructor"; }

	~OrderedQueue() { cout << "\nOrderedQueue destructor"; }

	ListIterator<T> begin()
	{
		ListIterator<T> it(head);
		return it;
	}
	ListIterator<T> end()
	{
		ListIterator<T> it(tail);
		return it;
	}

	void insert(T value)
	{
		num++;
		ListIterator<T> it = end();
		if (head == NULL)
		{
			Queue<T>::push(value);
			return;
		}
		if (value < it.ptr->getValue() || value == it.ptr->getValue())
		{
			Queue<T>::push(value);
			return;
		}
		it = begin();
		Element<T>* newelem = new Element<T>(value);
		if (value > it.ptr->getValue() || value == it.ptr->getValue())
		{
			newelem->setNext(head);
			newelem->getNext()->setPrevious(newelem);
			head = newelem;
			return;
		}

		while (value < it.ptr->getValue())
			it++;
		newelem->setNext(it.ptr);
		newelem->setPrevious(it.ptr->getPrevious());
		it.ptr->getPrevious()->setNext(newelem);
		it.ptr->setPrevious(newelem);
		return;
	}

	template <class T1>
	friend ostream& operator <<(ostream& s, OrderedQueue<T1>& q);

	template <class T2>
	friend OrderedQueue<T2> filter(LinkedListParent<T2>* q, bool(*predicate)(T2));
};



template<class T1>
ostream& operator <<(ostream& s, OrderedQueue<T1>& q)
{
	ListIterator<T1> it = q.begin();
	while (it != q.end())
	{
		cout << *it << " ";
		it++;
	}
	cout << *it << " ";
	return s;
}

template <class T>
OrderedQueue<T> filter(LinkedListParent<T>* q, bool (*predicate)(T))
{
	OrderedQueue<T> res;
	for (ListIterator<T> it = (*q).begin(); it != (*q).end(); it++)
	{
		if (predicate((*it).getValue()))
			res.insert((*it).getValue());
	}
	return res;
}

bool iscube(int value)
{
	double a = (pow(abs(value), 1 / 3.0));
	return abs(a - round(a)) < 0.000001 ? 1 : 0;
}


int main()
{
	Queue<int> q;
	q.push(11);
	q.push(8);
	q.push(15);
	cout << q;
	try
	{
		OrderedQueue<programmer> q2;

		programmer a("aa", "aa", "aa", "aa", "aa", "aa", "aa", 5);
		programmer b("bb", "bb", "bb", "bb", "bb", "bb", "bb", 10);
		programmer c("cc", "cc", "cc", "cc", "cc", "cc", "cc", 2);
		programmer d("dd", "dd", "dd", "dd", "dd", "dd", "dd", 10);
		programmer e("ee", "ee", "ee", "ee", "ee", "ee", "ee", 1);


		q2.insert(e);
		q2.insert(b);
		q2.insert(c);
		q2.insert(a);
		q2.insert(d);

		cout << q2;

		LinkedListParent<int>* it = &q;

		OrderedQueue<int> q3 = filter(it, iscube);

		cout << "Filtered: " << q3;
	}

	catch (IteratorNullException e)
	{
		cout << "\nCaught IteratorNullException: "; e.print();
	}
	catch (Invalidlvlexception e)
	{
		cout << "\nCaught Invalidlvlexception: "; e.print();
	}
	Element<int>* e;
	e = q.pop();
	int res = e->getValue();
	cout << "\n" << res << " ";

	e = q.pop();
	res = e->getValue();
	cout << res << " ";

	e = q.pop();
	res = e->getValue();
	cout << res << " ";
}