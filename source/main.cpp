#include"set.cpp"
#include"book.h"
#include"functor.cpp"
#include"int_input.h"
#include<Windows.h>

void main()
{
	bool programm = true;
	set<Book> books;
	while (programm)
	{
		cout << "books..." << endl;
		cout << "1 - show all" << endl
			<< "2 - add new" << endl
			<< "3 - edit book" << endl
			<< "4 - delete book" << endl
			<< "5 - clear all info" << endl
			<< "6 - add random book" << endl
			<< "7 - exit..." << endl;
		int choise = int_enter(1, 7);
		switch (choise)
		{
		case 1:
			if (books.empty()) cout << "no books here..." << endl;
			else
			{
				books.show();
			}
			break;
		case 2:
		{
			Book book;
			cin >> book;
			books.insert(book);
		}
		break;
		case 3:
		{
			if (books.empty()) cout << "no books here..." << endl;
			else
			{
				Book book;
				cin >> book;
				books.edit(book);
			}
		}
		break;
		case 4:
		{
			if (books.empty()) cout << "no books here..." << endl;
			else
			{
				Book book;
				cin >> book;
				books.erase(book);
			}
		}
		break;
		case 5:
			books.clear();
			break;
		case 6:
		{
			Functor<Book> random;
			books.generate(random);
		}
		break;
		case 7:
			programm = false;
			break;
		}
	}

	return;
}