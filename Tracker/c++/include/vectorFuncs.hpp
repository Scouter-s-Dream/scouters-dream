#ifndef VECTOR_FUNCS__HPP
#define VECTOR_FUNCS__HPP

#include <iostream>
#include <vector>

using std::cout;
using std::vector;

template<typename T2>
void removeAtIndex(vector<T2> &vect, uint16_t index);

template<typename T2>
void removeAtIndex(vector<T2> &vect, uint16_t index){    
    //TODO add exception on size.
    vect.erase(vect.begin() + index);
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vector);

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vector){
    // Printing all the elements
    // using <<
    os << "[";
    for (auto element : vector) {
        os << element << " ";
    }
    os << "\b]";
    return os;
}

#endif