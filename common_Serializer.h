#ifndef CLASS_SERIALIZER
#define CLASS_SERIALIZER

#include <string>
class CommandAyuda;
class CommandRendirse;
class CommandNumber;

class Serializer {
public:
    //Convierte el comando obtenido en una cadena serializada con el protocolo
    //estipulado
    //Precondicion: result debe tener un tamaño de 1 bytes o mas.
    int serialize(const CommandAyuda command, char* result) const;
    int serialize(const CommandRendirse command, char* result) const;
    //Precondicion: result debe tener un tamaño de 3 bytes o mas.
    int serialize(const CommandNumber command, char* result) const;
    //Convierte el string obtenido en una cadena serializada con
    //el protocolo estipulado
    //Precondicion: result debe tener como minimo, un tamaño igual
    //al de string + 4   
    int serialize(const std::string string, char* result) const;
    //Descerializa el mensaje, y devuelve un string 
    //con el mensaje descerializado
    const std::string deserialize(const char* string,bool mode) const;
};

#endif
