#include "common_Serializer.h"
#include <arpa/inet.h>
#include "common_CommandNumber.h"
#include <string>
#include <inttypes.h>
#define COMMAND true
#define STRING false

int Serializer::serialize(const CommandNumber commandNumber,char* result)const{
    result[0] = 'n';
    uint16_t number = (uint16_t) stoi(commandNumber.getCommand());
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

