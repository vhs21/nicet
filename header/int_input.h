#pragma once
#include<exception>
#include<iostream>

using namespace std;

class int_input_exception : public exception
{
public:
	int_input_exception();
	int_input_exception(char *);
	virtual ~int_input_exception();
};

class int_out_of_bounds_exception : public int_input_exception
{
public:
	int_out_of_bounds_exception();
	int_out_of_bounds_exception(char *);
	~int_out_of_bounds_exception();
};

int int_enter(int, int);