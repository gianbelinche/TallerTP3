#include "server_CircleVector.h"

CircleVector::CircleVector() : pos(0), vector() {}

void CircleVector::push_back(const uint16_t val){
    vector.push_back(val);
}

uint16_t CircleVector::next(){
    if (pos == vector.size()){
        pos = 0;
    }
    uint16_t ans = vector[pos];
    pos++;
    return ans;
}
