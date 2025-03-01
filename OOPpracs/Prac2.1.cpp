#include <map> 
#include <iostream> 
#include <list>
#include <set>

using namespace std;

class date
{
public:
	int Day;
	int Month;
	int Year;


	date()
	{
		Day = 1;
		Month = 1;
		Year = 0;
	}


	date(const int& day, const int& month, const int& year)
	{
		Day = day;
		Month = month;
		Year = year;
	}

	date(const date& dedate)
	{
		Day = dedate.Day;
		Month = dedate.Month;
		Year = dedate.Year;
	}


	bool operator == (const date& b) const
	{
		return (Day == b.Day && Month == b.Month && Year == b.Year) ? true : false;
	}

	bool operator != (const date& b) const
	{
		return (Day == b.Day && Month == b.Month && Year == b.Year) ? false : true;
	}

	bool operator > (const date& b) const
	{
		if (Year == b.Year)
		{
			if (Month == b.Month)
			{
				if (Day == b.Day) return 0;
				return (Day > b.Day) ? 1 : 0;
			}	
			return (Month > b.Month) ? 1 : 0;
		}
		else {
			return (Year > b.Year) ? 1 : 0;
		}
	}

	bool operator < (const date& b) const
	{
		if (Year == b.Year)
		{
			if (Month == b.Month)
			{
				if (Day == b.Day) return 0;
				return (Day < b.Day) ? 1 : 0;
			}
			return (Month < b.Month) ? 1 : 0;
		}
		else {
			return (Year < b.Year) ? 1 : 0;
		}
	}

	friend ostream& operator<<(ostream& os, const date& b);
};

ostream& operator<<(ostream& os, const date& b)
{
	os << b.Day << '/' << b.Month << '/' << b.Year;
	return os;
}


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

class KeyException : public Exception
{
protected:
	string Key;
public:
	KeyException(const char* s, string k) : Exception(s) { Key = k; }
	KeyException(const KeyException& c) : Exception(c) { Key = c.Key; }

	virtual void print()
	{
		cout << Key << " Another value already have THIS key " << str;
	}
};


void show(map<string, date>& tree)
{
	for (map<string, date>::iterator iterator_tree = tree.begin(); iterator_tree != tree.end(); iterator_tree++)
	{
		cout << "key: " << iterator_tree->first << ", value: " << iterator_tree->second << endl;
	}
	cout << endl;
}


list<date> key_search(map<string, date>& tree, string key)
{
	list<date> res;
	auto iterator_tree = tree.find(key);
	if (iterator_tree != tree.end())
		res.push_back(iterator_tree->second);
	return res;
}


list<string> search_by_value(map<string, date>& tree, date value)
{
	list<string> res;
	auto iterator_tree = tree.begin();
	while (iterator_tree != tree.end())
	{
		res.push_back(iterator_tree->first);
		iterator_tree++;
	}
	return res;
}


set<date> diff_values(map<string, date>& tree)
{
	set<date> res_values;
	for (map<string, date>::iterator iterator_tree = tree.begin(); iterator_tree != tree.end(); iterator_tree++)
	{
		res_values.insert(iterator_tree->second);
	}
	return res_values;
}


map<string, date> filter(map<string, date>& tree, date threshold)
{
	map<string, date> res_values;
	for (map<string, date>::iterator iterator_tree = tree.begin(); iterator_tree != tree.end(); iterator_tree++)
	{
		if (iterator_tree->second > threshold)
		{
			res_values[iterator_tree->first] = (iterator_tree->second);
		}
	}
	return res_values;
}


int main()
{

	map<string, date> students;
	students["Petrov"] = date(5, 12, 2003);
	students["Ivanov"] = date(14, 3, 1996);
	students["Sidorov"] = date(7, 7, 1997);
	students["Nikolaev"] = date(19, 2, 1861);
	students["Abramov"] = date(1, 1, 2011);
	students["Leonov"] = date(1, 1, 2011);
	
	cout << "-----------------------------" << endl;

	show(students);

	cout << "-----------------------------" << endl;

	list<date> aaa = key_search(students, "Nikolaev");
	list<date>::iterator bbb = aaa.begin();
	cout << *bbb << endl;

	cout << "-----------------------------" << endl;

	list<string> asd = search_by_value(students, date(1, 1, 2011));
	list<string>::iterator dsa = asd.begin();
	cout << *dsa << endl;

	cout << "-----------------------------" << endl;

	set<date> ccc = diff_values(students);
	set<date>::iterator ddd = ccc.begin();
	cout << "diff_values: " << endl;
	while (ddd != ccc.end())
	{
		cout << *ddd << endl;
		ddd++;
	}

	cout << "----------------------------" << endl;
	date threashold = date(1, 1, 2000);
	map<string, date> fff = filter(students, threashold);
	map<string, date>::iterator ggg = fff.begin();
	while (ggg != fff.end())
	{
		cout << "Key: " << ggg->first << ", value: " << ggg->second << "\n";
		ggg++;
	}

	cout << "----------------------------" << endl;

	students["Abramov"] = date(1, 1, 20111);
	show(students);

}