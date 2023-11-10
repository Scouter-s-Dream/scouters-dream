#ifndef __printVector__HPP
#define __printVector__HPP

#include <stdio.h>
#include <iostream>
#include <stdexcept>

using std::vector;

template <typename S>
std::ostream& operator<<(std::ostream& os, const std::vector<S>& vector){
    // Printing all the elements
    // using <<
    os << "[";
    for (auto element : vector) {
        os << element << " ";
    }
    os << "\b]";
    return os;
}

std::vector<vector<int>> vector1Dto2D(std::vector<int> input, std::vector<size_t> newShape);

#endif