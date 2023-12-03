#include "vectorFuncs.hpp"

template<typename T> void removeAtIndex(vector<T> &vect, uint16_t index){    
    //TODO add exception on size.
    vect.erase(vect.begin() + index);
}





