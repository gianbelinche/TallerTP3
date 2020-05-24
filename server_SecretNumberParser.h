#ifndef CLASS_SECRET_NUMBER_PARSER
#define CLASS_SECRET_NUMBER_PARSER

#include <iostream>
#include <fstream>
#include <string>
#include "server_CircleVector.h"

class SecretNumberParser {
private:
    std::ifstream file;
public:
    //Parsea el archivo de entrada, y guarda el contenido en el vector
    //Si algun numero no cumple las condiciones necesarias, tira excepcion
    void parse(std::string file_name,CircleVector&& vector);
};

#endif
