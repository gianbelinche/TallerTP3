#ifndef CLASS_STADISTICS
#define CLASS_STADISTICS

#include <mutex>

class Stadistics {
private:
    int wins;
    int loses;
    std::mutex m;
public:
    Stadistics() : wins(0), loses(0) {}
    Stadistics (const Stadistics& copy) = delete;
    Stadistics& operator=(const Stadistics& copy) = delete;
    void win();
    void lose();
    void print();    
};

#endif
