#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>

using namespace std;

class Book
{
	string name, author, genre;
	int release_year;
public:
	Book();
	~Book();
	Book(string, string, string, int);
	Book(const Book &);

	string get_name();
	string get_author();
	string get_genre();
	int get_release_year();

	void set_name(string);
	void set_author(string);
	void set_genre(string);
	void set_release_year(int);

	Book& operator=(Book&);
	bool operator<(const Book&);
	bool operator<=(const Book&);
	bool operator>(const Book&);
	bool operator>=(const Book&);
	bool operator==(const Book&);
	bool operator!=(const Book&);

	friend ostream& operator<<(ostream&, const Book&);
	friend istream& operator>>(istream&, Book&);

	static Book gen();
};