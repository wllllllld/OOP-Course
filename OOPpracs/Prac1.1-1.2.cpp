#include <list> 
#include <string>
#include <iostream> 
using namespace std;

class Student
{
public:
	string firstname, lastname, address;
	char male;
	int birthday, grade;

	Student()
	{
		male = '-';
		birthday = 0;
		grade = 0;
	}

	Student(const string& Firstname, const string& Lastname, const string& Address, char Male, int Birthday, int Grade)
	{
		firstname = Firstname;
		lastname = Lastname;
		address = Address;
		male = Male;
		birthday = Birthday;
		grade = Grade;
	}

	Student(const Student& stud)
	{
		firstname = stud.firstname;
		lastname = stud.lastname;
		address = stud.address;
		male = stud.male;
		birthday = stud.birthday;
		grade = stud.grade;
	}

	~Student() {}

	friend ostream& operator << (ostream& s, const Student& value);
	friend istream& operator >> (istream& s, Student& value);

	bool operator < (const Student& stud) const
	{
		if (birthday < stud.birthday)
			return true;

		if (lastname < stud.lastname)
			return true;

		if (firstname < stud.firstname)
			return true;

		return false;
	}

	bool operator > (const Student& stud) const
	{
		if (birthday > stud.birthday)
			return true;

		if (lastname > stud.lastname)
			return true;

		if (firstname > stud.firstname)
			return true;

		return false;
	}

	bool operator == (const Student& stud) const
	{
		return firstname == stud.firstname &&
			lastname == stud.lastname &&
			birthday == stud.birthday;
	}
};

ostream& operator << (ostream& stream, const Student& value)
{
	return stream << value.firstname << ' ' << value.lastname << ' ' << value.address << ' ' << value.male << ' ' << value.birthday << ' ' << value.grade;
}

istream& operator >> (istream& stream, Student& value)
{
	return stream >> value.firstname >> value.lastname >> value.address >> value.male >> value.birthday >> value.grade;
}


bool predict(int x) { return x % 3 == 0; }


template<class T>
void push(list<T>& lst, T element)
{
	typename list<T>::iterator p;

	for (p = lst.begin(); p != lst.end(); p++)
		if (*p > element)
			break;

	lst.insert(p, element);
}


template<class T>
typename list<T>::iterator pop(list<T>& lst)
{
	typename list<T>::iterator it = lst.end();
	it--;
	lst.erase(it);
	return it;
}


template<class T>
list<T> filter(const list<T>& source, bool(*pred)(T))
{
	list<T> result;

	for (T item : source)
		if (pred(item))
			result.push_back(item);

	return result;
}


template<class T>
void print(const list<T>& lst)
{
	for (typename list<T>::const_iterator p = lst.begin(); p != lst.end(); p++)
		cout << *p << '\n';

	cout << endl;
}

int main()
{

	list<char> lst;

	for (int i = 0; i < 10; i += 2)
		lst.push_back('A' + i);

	push(lst, 'B');

	print(lst);

	char popped = *pop(lst);

	//cout << "Popped: " << popped << endl;

	list<Student> students;
	push(students, Student("Antonina", "Petrova", "Moscow", 'w', 2007, 8));
	push(students, Student("Boris", "Sergeev", "London", 'm', 2006, 7));
	push(students, Student("Vsevolod", "Kuznetsov", "Minsk", 'm', 2005, 6));
	push(students, Student("Petr", "Li", "Khabarovsk", 'm', 2004, 5));
	print(students);
	
	list<int> numbers;

	for (int i = 0; i < 15; i++)
		numbers.push_back(i);

	cout << "Numbers:\n";
	print(numbers);

	list<int> predicted = filter(numbers, predict);

	cout << "Predicted:\n";
	print(predicted);

	return 0;
}


