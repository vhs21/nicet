#include"book.h"

Book::Book() {}

Book::~Book() {}

Book::Book(string name, string author, string genre, int release_year)
{
	this->name = name;
	this->author = author;
	this->genre = genre;
	this->release_year = release_year;
}

Book::Book(const Book & book)
{
	this->name = book.name;
	this->author = book.author;
	this->genre = book.genre;
	this->release_year = book.release_year;
}


string Book::get_name()
{
	return this->name;
}

string Book::get_author()
{
	return this->author;
}

string Book::get_genre()
{
	return this->genre;
}

int Book::get_release_year()
{
	return this->release_year;
}


void Book::set_name(string name)
{
	this->name = name;
}

void Book::set_author(string author)
{
	this->author = author;
}

void Book::set_genre(string genre)
{
	this->genre = genre;
}

void Book::set_release_year(int release_year)
{
	this->release_year = release_year;
}


Book& Book::operator = (Book & book)
{
	if (this == &book) return book;
	this->name = book.name;
	this->author = book.author;
	this->genre = book.genre;
	this->release_year = book.release_year;
	return *this;
}

bool Book::operator<(const Book & book)
{
	int result_name = strcmp(this->name.c_str(), book.name.c_str());
	if (result_name < 0) return true;
	else if (result_name > 0)return false;
	else
	{
		if (this->release_year < book.release_year) return true;
		else if (this->release_year > book.release_year) return false;
		else
		{
			int result_author = strcmp(this->author.c_str(), book.author.c_str());
			if (result_author < 0) return true;
			else if (result_author > 0) return false;
			else
			{
				int result_genre = strcmp(this->genre.c_str(), book.genre.c_str());
				if (result_genre < 0) return true;
				else return false;
			}
		}
	}
}

bool Book::operator<=(const Book & book)
{
	int result_name = strcmp(this->name.c_str(), book.name.c_str());
	if (result_name <= 0) return true;
	else return false;
}

bool Book::operator>(const Book & book)
{
	int result_name = strcmp(this->name.c_str(), book.name.c_str());
	if (result_name > 0) return true;
	else if (result_name < 0)return false;
	else
	{
		if (this->release_year > book.release_year) return true;
		else if (this->release_year < book.release_year) return false;
		else
		{
			int result_author = strcmp(this->author.c_str(), book.author.c_str());
			if (result_author > 0) return true;
			else if (result_author < 0) return false;
			else
			{
				int result_genre = strcmp(this->genre.c_str(), book.genre.c_str());
				if (result_genre > 0) return true;
				else return false;
			}
		}
	}
}

bool Book::operator>=(const Book & book)
{
	int result_name = strcmp(this->name.c_str(), book.name.c_str());
	if (result_name >= 0) return true;
	else return false;
}

bool Book::operator==(const Book & book)
{
	if (this->name != book.name) return false;
	if (this->author != book.author) return false;
	if (this->genre != book.genre) return false;
	if (this->release_year != book.release_year) return false;
	return true;
}

bool Book::operator!=(const Book & book)
{
	if (this->name != book.name) return true;
	if (this->author != book.author) return true;
	if (this->genre != book.genre) return true;
	if (this->release_year != book.release_year) return true;
	return false;
}


ostream& operator<<(ostream& show, const Book& book)
{
	show << "\"" << book.name.c_str() << "\"" << ", "
		<< book.author.c_str() << ", "
		<< book.genre.c_str() << ", "
		<< book.release_year << ".";
	return show;
}

istream& operator>>(istream& enter, Book& book)
{
	cout << "  book name: ";
	_flushall();
	cin.ignore();
	getline(enter, book.name);
	cout << "  author: ";
	_flushall();
	getline(enter, book.author);
	cout << "  genre: ";
	_flushall();
	getline(enter, book.genre);
	cout << "  release year: ";
	enter >> book.release_year;
	return enter;
}


Book Book::gen()
{
	srand(static_cast<unsigned int>(time(NULL)));
	const int first_year = 1800, last_year = 2016, names_size = 8, authors_size = 4, genres_size = 7;
	const string names[names_size] = { "Hunt", "World Beyond the Wall", "Flowers", "Insane Samurai", "Adult Gambino", "Mighty Fall", "Prayer", "Universe TV" };
	const string authors[authors_size] = { "Hazel J. R.", "Aretha B. H.", "Ivo P. M.", "Taryn B. R." };
	const string genres[genres_size] = { "romance", "science fiction", "comedy", "tragedy", "adventure", "fantasy", "dystopia" };
	string name = names[rand() % names_size];
	string author = authors[rand() % authors_size];
	string genre = genres[rand() % genres_size];
	int year = (rand() % last_year);
	return Book(name, author, genre, year);
}