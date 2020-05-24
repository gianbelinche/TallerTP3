#ifndef CLASS_COMMAND_RENDIRSE
#define CLASS_COMMAND_RENDIRSE
#include "common_Command.h"
#include <string>

class CommandRendirse : public Command {
public:
    explicit CommandRendirse(std::string command);
    bool isValid() const override;
    void send(Socket&& socket) const override;
};

#endif
