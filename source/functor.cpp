#include"functor.h"

template<class T>
T Functor<T>::operator()()
{
	return T::gen();
}