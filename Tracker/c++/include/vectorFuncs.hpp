#ifndef VECTOR_FUNCS__HPP
#define VECTOR_FUNCS__HPP

#include <iostream>
#include <vector>

using std::cout;
using std::vector;

template<typename T> void removeAtIndex(vector<T> &vect, uint16_t index);

template <typename T> std::ostream& operator<<(std::ostream& os, const std::vector<T>& vector);

#endif