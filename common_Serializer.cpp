#include "common_Serializer.h"
#include <arpa/inet.h>
#include "common_CommandAyuda.h"
#include "common_CommandRendirse.h"
#include "common_CommandNumber.h"
#include <string>
#define COMMAND true
#define STRING false

int Serializer::serialize(const CommandNumber commandNumber,char* result)const{
    result[0] = 'n';
    short number = (short) stoi(commandNumber.getCommand());
    number = htons(number);
    char* ptr = (char*) &number;
    result[1] = ptr[0];
    result[2] = ptr[1];
    return 3;
}

int Serializer::serialize(const std::string string, char* result) const{
    int length = htonl(string.length());
    char* ptr = (char*) &length;
    result[0] = ptr[0];
    result[1] = ptr[1];
    result[2] = ptr[2];
    result[3] = ptr[3];
    for (unsigned int i = 0; i < string.length(); i++){
        result[i + 4] = string[i];
    }
    return length + 4;
}

