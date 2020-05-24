#include "server_CircleVector.h"

CircleVector::CircleVector() : pos(0), vector() {}

void CircleVector::push_back(const short val){
    vector.push_back(val);
}

short CircleVector::next(){
    if (pos == vector.size()){
        pos = 0;
    }
    short ans = vector[pos];
    pos++;
    return ans;
}
