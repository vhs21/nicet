#include<iostream>

using namespace std;

template<class T>
class Functor
{
public:
	T operator()();
};