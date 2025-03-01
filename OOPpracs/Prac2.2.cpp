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



void show(multimap<string, date>& tree)
{
	for (multimap<string, date>::iterator iterator_tree = tree.begin(); iterator_tree != tree.end(); iterator_tree++)
	{
		cout << "key: " << iterator_tree->first << ", value: " << iterator_tree->second << endl;
	}
	cout << endl;
}


list<date> key_search(multimap<string, date>& tree, string key)
{
	list<date> res;
	auto iterator_tree = tree.find(key);
	if (iterator_tree != tree.end())
		res.push_back(iterator_tree->second);
	return res;
}


list<string> search_by_value(multimap<string, date>& tree, date value)
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


set<date> diff_values(multimap<string, date>& tree)
{
	set<date> res_values;
	for (multimap<string, date>::iterator iterator_tree = tree.begin(); iterator_tree != tree.end(); iterator_tree++)
	{
		res_values.insert(iterator_tree->second);
	}
	return res_values;
}


multimap<string, date> filter(multimap<string, date>& tree, date threshold)
{
	multimap<string, date> res_values;
	for (multimap<string, date>::iterator iterator_tree = tree.begin(); iterator_tree != tree.end(); iterator_tree++)
	{
		if (iterator_tree->second > threshold)
		{
			res_values.emplace(iterator_tree->first, iterator_tree->second);
		}
	}
	return res_values;
}

list<pair<string, date>> diff_values_onekey(multimap<string, date>& tree, string key)
{
	list<pair<string, date>> res;
	for (auto iterator_tree = tree.begin(); iterator_tree != tree.end(); iterator_tree++)
	{
		if (iterator_tree->first == key)
			res.push_back(*iterator_tree);
	}
	return res;
}

int main()
{
	multimap<string, date> students;

	students.emplace(string("Petrov"), date(8, 12, 2006));
	students.emplace(string("Ivanov"), date(10, 10, 2004));
	students.emplace(string("Sidorov"), date(11, 8, 2003));
	students.emplace(string("Sidorov"), date(31, 7, 1998));

	show(students);

	list<pair<string, date>> l;

	string s = "Sidorov";

	l = diff_values_onekey(students, s);

	list<pair<string, date>>::iterator l_i = l.begin();
	while (l_i != l.end())
	{
		cout << l_i->first << ' ' << l_i->second << endl;
		l_i++;
	}

}