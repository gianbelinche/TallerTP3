#include "common_Command.h"
#include <arpa/inet.h>
#include <string>

std::string Command::recv(Socket&& socket) const{
    char ans[4];
    socket.Recv(ans,4);
    int size = ntohl(*(int*) ans);
    char* ans2 = (char*) malloc(size + 1);
    socket.Recv(ans2,size);
    ans2[size] = '\0';
    std::string answer(ans2);
    free(ans2);
    return answer;
}
