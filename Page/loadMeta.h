#include"Page.h"
#include"../Utils/myStrtok.h"


void Page::loadMeta() {

    // abrir el archivo de metadta del directorio de sectores
    ifstream directory("./Disk/data/meta/directory");

    if(directory.is_open()) {
        while (directory.getline(buffer, lenBuffer))
        {
            char * token = myStrtok(buffer, " ");

            if(atoi(token) >= l1 && atoi(token) <= l2) {
                bool isFirst = true;
                int sector = atoi(token); 
                while (token != nullptr)
                {
                    if(!isFirst) {
                        freeSpace[sector]++;
                    }

                    else {
                        freeSpace[sector] = -1;
                        isFirst = false;
                    }

                    token = myStrtok(nullptr, " ");
                }
            }            
        }

        directory.close();
    } else {
        cout<<"Problem open directory"<<endl;
        return;
    }

    for (const auto& pair : freeSpace) {
        std::cout << "Clave: " << pair.first << ", Valor: " << pair.second << std::endl;
    }

}