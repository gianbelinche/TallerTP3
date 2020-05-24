#ifndef CLASS_CIRCLE_VECTOR
#define CLASS_CIRCLE_VECTOR

#include <vector>
class CircleVector {
private:
    unsigned int pos;
    std::vector<short> vector;  
public:
    CircleVector();
    //CircleVector(CircleVector& copy);
    //CircleVector& operator=(CircleVector& copy);
    void push_back(const short val);
    short next();
};

#endif
