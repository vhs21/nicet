#include"int_input.h"

int_input_exception::int_input_exception() {}

int_input_exception::int_input_exception(char *str) :exception(str) {}

int_input_exception::~int_input_exception() {}

int_out_of_bounds_exception::int_out_of_bounds_exception() : int_input_exception() {}

int_out_of_bounds_exception::int_out_of_bounds_exception(char *str) : int_input_exception(str) {}

int_out_of_bounds_exception::~int_out_of_bounds_exception() {}


int int_enter(int from, int to)
{
	int flag = 0, x;
	while (!flag)
	{
		try
		{
			cin.sync();
			cin.clear();
			cin >> x;
			if (!cin) throw int_input_exception("didn't you see? you need to enter a number.");
			else if (from == to) flag = 1;
			else if (x < from || x > to) throw int_out_of_bounds_exception("didn't you see the boundaries?");
			else flag = 1;
		}
		catch (int_out_of_bounds_exception int_out_of_bounds_exception)
		{
			cout << int_out_of_bounds_exception.what() << endl;
		}
		catch (int_input_exception int_input_exception)
		{
			cout << int_input_exception.what() << endl;
		}
	}
	return x;
}