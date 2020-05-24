#ifndef CLASS_COMMAND_NUMBER
#define CLASS_COMMAND_NUMBER
#include "common_Command.h"
#include <string>

class CommandNumber : public Command {
private:
    std::string isNumberValid(short number) const; //Esto va para server    
public:
    explicit CommandNumber(std::string command);
    bool isValid() const override;
    void send(Socket&& socket) const override;
    std::string getCommand() const;    
};

#endif
