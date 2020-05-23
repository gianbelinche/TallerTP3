#include "server_CircleVector.h"

CircleVector::CircleVector() : pos(0), vector() {}

/*
CircleVector::CircleVector(CircleVector& copy){
    for (unsigned int i = 0; i < copy.vector.size(); i++){
        vector[i] = (copy.vector)[i];
    }
    this->pos = 0;
}

CircleVector& CircleVector::operator=(CircleVector& copy){
    this->vector = other.vector; //intento 1
    for (unsigned int i = 0; i < copy.vector.size(); i++){ //intento 2
        vector[i] = (copy.vector)[i];
    }
    this->pos = 0;
    return *this;
}*/

void CircleVector::push_back (const short val){
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
