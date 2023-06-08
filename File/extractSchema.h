#ifndef EXTRACT_SCHEMA
#define EXTRACT_SCHEMA

#include"File.h"

void File::extractSchema() {
    ifstream schema("./docs/schema");

    // seteamos el array que guardará los espacios que alamacena cada columna
    this->columnBytes = new int[numberColumns];
    
    // fase de conteo de bytes
    if(schema.is_open()) {
        while (schema.getline(buffer, lenBuffer))
        {
            this->numberColumns++;
        }
        schema.close();
    } else {
      cout<<"Error open schema file"<<endl;  
    }
    this->numberColumns -= 2;



    // fase de extraccion de pesos de columnas
    this->columnBytes = new int[numberColumns];

    // regex para extraer los pesos
    regex numberRegex(R"(\d+)");
    schema.open("./docs/schema");

    if (schema.is_open()) {
        char type[256];
        
        int it = 0;
        while (schema.getline(buffer, lenBuffer))
        {
            const char* input = buffer;
            const char* end = buffer + strlen(buffer);

            std::regex_iterator<const char*> iterator(input, end, numberRegex);
            std::regex_iterator<const char*> endIterator;
            while (iterator != endIterator) {
                cmatch match = *iterator;
                columnBytes[it++] = atoi(match.str().c_str());
                this->totalRegisterBytes += atoi(match.str().c_str());
                ++iterator;
            }
        }

        schema.close();
    } else {
        cout<<"No se puede abrir"<<endl;
    }

    
    delete buffer;

    buffer = new char[totalRegisterBytes];

}

#endif