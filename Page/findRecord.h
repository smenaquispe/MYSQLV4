#include"Page.h"

int Page::findRecord(int idRecord) {


    int lenBuffer = 1024;

    char buffer[lenBuffer];

     // abrir el archivo de metadta del directorio de sectores
    ifstream directory("./Disk/data/meta/directory");

    int sectorNumber = -1; // donde se guardará el sector que almacena ese registro

    if(directory.is_open()) {
        while (directory.getline(buffer, lenBuffer))
        {
            char * token = myStrtok(buffer, " ");

            if(atoi(token) >= l1 && atoi(token) <= l2) {
        
                bool isFirst = true; 

                int temp = atoi(token);
                while (token != nullptr)
                {
                    if(!isFirst) {
                        if(atoi(token) == idRecord) {
                            sectorNumber = temp;
                            break;
                        }
                    }

                    if(isFirst) isFirst = false;
                    token = myStrtok(nullptr, " ");
                }
            }            
        }

        directory.close();
    } else {
        cout<<"Problem open directory"<<endl;
        return -1;
    }

    // no se encuentra el registro dentro del bloque
    if(sectorNumber == -1) {
        cout<<"Records doesnt find in any sector of this cluster"<<endl;
    } 

    return sectorNumber;
}