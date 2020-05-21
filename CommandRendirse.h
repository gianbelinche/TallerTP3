#ifndef CLASS_COMMAND_RENDIRSE
#define CLASS_COMMAND_RENDIRSE
#include "Command.h"

class CommandRendirse : public Command {
public:
    CommandRendirse(std::string command);
    bool isValid() const override;
    void send() const override;
    std::string recv() const override;    
};

#endif
