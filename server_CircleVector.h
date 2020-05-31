#ifndef CLASS_CIRCLE_VECTOR
#define CLASS_CIRCLE_VECTOR

#include <vector>
#include <inttypes.h>
class CircleVector {
private:
    unsigned int pos;
    std::vector<uint16_t> vector;  
public:
    CircleVector();
    //Inserta un elemento al final del vector
    void push_back(const uint16_t val);
    //Devuelve el siguiente elemento del vector
    //En caso de llegar al final, vuelve a empezar desde el principio
    uint16_t next();
};

#endif
