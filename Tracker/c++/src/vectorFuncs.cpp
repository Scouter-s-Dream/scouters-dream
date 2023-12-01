#include "vectorFuncs.hpp"

template<typename T> void removeAtIndex(vector<T> &vect, uint16_t index){    
    //TODO add exception on size.
    vect.erase(vect.begin() + index);
}

template <typename T> std::ostream& operator<<(std::ostream& os, const std::vector<T>& vector){
    os << "[";
    for (auto element : vector) {
        os << element << " ";
    }
    os << "\b]";
    return os;
}




