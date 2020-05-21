#ifndef CLASS_COMMAND_NUMBER
#define CLASS_COMMAND_NUMBER
#include "Command.h"

class CommandNumber : public Command {
private:
    std::string isNumberValid(short number) const; //Esto va para server    
public:
    CommandNumber(std::string command);
    bool isValid() const override;
    void send() const override;
    std::string recv() const override;
    std::string getCommand() const;    
};

#endif