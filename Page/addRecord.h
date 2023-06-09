#include"Page.h"

void Page::addRecord() {
    // abrimos el archivo que contiene informacion del nuevo registro
    fstream input("./docs/input");

    int sectorSelected;
    for (auto it = freeSpace.begin(); it != freeSpace.end(); ++it) {
        
        // se encontró el sector con espacio libre
        
        if(it->second < maximumSector) {
            sectorSelected = it->first;
            break;
        }
    }

    vector<string> inputs;
    regex regex(R"(\(([^)]+)\))");

    if(input.is_open()) {
        while (input.getline(buffer, lenBuffer))
        {
            const char* input = buffer;
            const char* end = buffer + strlen(buffer);

            std::regex_iterator<const char*> iterator(input, end, regex);
            std::regex_iterator<const char*> endIterator;

            while (iterator != endIterator) {
                cmatch match = *iterator;
                std::string content = match.str().substr(1, match.str().length() - 2);
                inputs.push_back(content);
                ++iterator;
            }
        }

        input.close();
    } else {
        cout<<"Problem open input file"<<endl;
    }

    // abrimos el sector que queremos modificar
    ofstream sector("./Disk/data/sectors/" + to_string(sectorSelected), ios::app);
    fstream metaSector("./Disk/data/meta/sectors" + to_string(sectorSelected));
    fstream directory("./Disk/data/meta/directory");

    /*
        1. leer el meta y sacar donde es que tengo un espacio en blanco
        2. el meta tiene que retornar, punto inicio 
    */

    // agrega al sector
    for(int i = 0; i < inputs.size(); i++){
        sector<<inputs[i];
    }

    ofstream temp("./Disk/data/meta/temp");

    // modificamos el directorio
    if(directory.is_open()) {
        while (directory.getline(buffer, lenBuffer))
        {
            char * token = myStrtok(buffer, " ");

            if(sectorSelected == atoi(token)) {
                bool first = true;
                while (token != nullptr)
                {
                    if(!first) {
                        if(atoi(token))
                            temp<<atoi(token)<<" ";
                    } 

                    if(first) {
                        temp<<atoi(token)<<" ";
                        first = false;
                    } 
                    token = myStrtok(nullptr, " ");
                }

                temp<<inputs[0]; // agregamos el nuevo id                           
                
            } else {
                while (token != nullptr)
                {
                    temp<<token<<" ";
                    token = myStrtok(nullptr, " ");
                }
            }
            
            temp<<endl;
        }
        directory.close();
        temp.close();
    } else {
        cout<<"Error open directory file"<<endl;
    }

    remove("./Disk/data/meta/directory");
    rename("./Disk/data/meta/temp", "./Disk/data/meta/directory");

    /*
        tercera parte, modificar la metadata
    */
}