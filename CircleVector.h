#include <vector>
class CircleVector {
private:
    unsigned int pos;
    std::vector<short> vector;  
public:
    CircleVector();
    CircleVector(CircleVector& copy);
    void push_back (const short val);
    short next();    
};