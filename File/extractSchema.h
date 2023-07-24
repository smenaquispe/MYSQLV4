#ifndef EXTRACT_SCHEMA
#define EXTRACT_SCHEMA

#include"File.h"

void File::extractSchema(string schemaFile) {

    ifstream schema(schemaFile);
    ofstream schema_output("./Disk/data/meta/schema");

    // regex para extraer los pesos
    regex numberRegex(R"(\d+)");
   
    if (schema.is_open()) {
        while (schema.getline(buffer, lenBuffer))
        {

            const char* input = buffer;
            const char* end = buffer + strlen(buffer);

            std::regex_iterator<const char*> iterator(input, end, numberRegex);
            std::regex_iterator<const char*> endIterator;
           
            while (iterator != endIterator) {
                cmatch match = *iterator;
                schema_output<<match.str()<<endl;
                this->totalRegisterBytes += atoi(match.str().c_str());
                ++iterator;
                numberColumns++;
            }
        }

        schema.close();
        schema_output.close();
    } else {
        cout<<"No se puede abrir"<<endl;
    }


}

#endif