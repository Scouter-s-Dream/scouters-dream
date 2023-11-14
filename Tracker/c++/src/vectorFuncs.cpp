#include "vectorFuncs.hpp"

using std::vector;

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

vector<vector<int>> vector1Dto2D(vector<int> input, vector<size_t> newShape){

    if (newShape.size() != 2){
        throw std::invalid_argument( "new shape must contain 2 items" );
    }

    if (!(input.size() == newShape[0] * newShape[1])){
        throw std::invalid_argument( "input shape and the wanted shape dont align" );
    }
    
    vector<vector<int>> out(newShape[0]);

    for (int i = 0, stop = newShape[0]; i < stop; i++){
        out[i].resize(newShape[1]);
    }

    for (int i = 0, stop = input.size(); i < stop; i++){
        int y = i / newShape[1];
        int x = i % newShape[1];
        out[y][x] = input[i];

    }

    return out;
}


