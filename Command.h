#ifndef CLASS_COMMAND
#define CLASS_COMMAND

#include <string>
class Command {
protected:
    std::string command;    
public:
    Command() {}
    Command(std::string command) : command(command) {}
    virtual bool isValid() const {return false;}
    virtual void send() const {}
    virtual std::string recv() const {return "";}
    virtual ~Command() {}
};

#endif
