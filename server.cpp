#include "server_Initializer.h"
#include "common_OSError.h"
#include <iostream>
#define UNKNOWN_ERROR "Unknown error\n"

int main(int argc,char* argv[]){
    try {
        Initializer initializer;
        return initializer.initialice(argc,argv);
    } catch(OSError& e){
        std::cerr << e.what();
        return 1;
    } catch(...){
        std::cerr << UNKNOWN_ERROR;
    }
}
