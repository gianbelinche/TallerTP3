#ifndef CLASS_COMMAND_AYUDA
#define CLASS_COMMAND_AYUDA

#include "Command.h"
#include <string>

class CommandAyuda : public Command {
public:
    CommandAyuda(std::string command);
    bool isValid() const override;
    void send() const override;
    std::string recv() const override;    
};

#endif
