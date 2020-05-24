#ifndef CLASS_CIRCLE_VECTOR
#define CLASS_CIRCLE_VECTOR

#include <vector>
class CircleVector {
private:
    unsigned int pos;
    std::vector<short> vector;  
public:
    CircleVector();
    //Inserta un elemento al final del vector
    void push_back(const short val);
    //Devuelve el siguiente elemento del vector
    //En caso de llegar al final, vuelve a empezar desde el principio
    short next();
};

#endif
