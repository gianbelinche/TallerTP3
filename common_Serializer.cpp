#include "common_Serializer.h"
#include <arpa/inet.h>
#include "common_CommandAyuda.h"
#include "common_CommandRendirse.h"
#include "common_CommandNumber.h"
#include <string>
#define COMMAND true
#define STRING false

int Serializer::serialize(const CommandAyuda command, char* result) const{
    result[0] = 'h';
    return 1;
}

int Serializer::serialize(const CommandRendirse command, char* result) const{
    result[0] = 's';
    return 1;
}

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

const std::string Serializer::deserialize(const char* string,bool mode) const {
    std::string answer(string,1);
    if (mode == COMMAND){
        return answer;
    }
    char length[4];
    length[0] = string[0];
    length[1] = string[1];
    length[2] = string[2];
    length[3] = string[3];
    int length_int = ntohl(*(int*) length);
    std::string ans;
    for (int i = 0; i<length_int; i++){
        ans.append(1,string[i + 4]);
    }
    return ans;
}
