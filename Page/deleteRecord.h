#include"Page.h"

void Page::deleteRecord(int idRecord) {
    int sectorSelected = this->findRecord(idRecord);
    if(sectorSelected == -1) return;

    // ahora si procedemos a eliminar el sector
    /*
        la tecnica de borrado es la siguiente:
            se borra directamente todo lo que ocupa el record
            y el espacio libre se mueve directamente al final del sector
            luego hacer un rework de la metadata del sector
            y restar en el free space
    */

    // 1ro modificar el archivo sector, retirando el la informacion del sector a eliminar
    ifstream sector("./Disk/data/sectors/" + to_string(sectorSelected));
    ifstream metaSector("./Disk/data/meta/sectors/" + to_string(sectorSelected));

    sector.getline(buffer, lenBuffer);

    /*
        el algoritmo será contar cuanto mide cada sector dinamicamente
    */

    char * auxBuffer = new char[lenBuffer];
    
    int puntoInicio, puntoFinal;
    int id; // para extraer y comprobar el id
    int posId = 0; // en que posicon se encuentra dentro del sector

    if(metaSector.is_open()) {
        
        int pos = 0;
        int countRecords = 1;

        
        while (metaSector.getline(auxBuffer, lenBuffer)) {
            
            bool isId = true; // cuando imprime por primera vez es el id
            int countColumns = 0;
            char * token = myStrtok(auxBuffer, " ");
            int a, b;
            bool first = true;

            while (token != nullptr)
            {
                if(strcmp(token, ",") && first) {
                    a = atoi(token);
                    first = false;
                }

                else if(strcmp(token, ",") && !first) {
                    b = atoi(token);
                    first = true;
                }

                // caso solo un numero
                else if(!strcmp(token, ",") && !first) {
                    b = a;
                    first = true;
                    pos += 1;
                
                    if(countColumns == 0) puntoInicio = pos;
                    puntoFinal = pos;

                    countColumns++;
                }

                else if(!strcmp(token, ",") && first) {
                    if((b - a) == 0){
                        pos += 1;
                    } else {
                        if(isId) {
                            string numberString(buffer + pos, b - a);
                            id = stoi(numberString);
                            isId = false;
                        }
                        pos += b - a;
                    }

                    if(countColumns == 0) puntoInicio = pos;
                    puntoFinal = pos;

                    countColumns++;
                }

                token = myStrtok(nullptr, " ");
            }

            // aqui extraigo el punto de inicio y el punto de final 
            // que alcanza el registro que quiero eliminar
            puntoFinal--;
            puntoInicio--;
            countRecords++;
            
            if(id == idRecord) {
                break;
            }

            posId++;
        }
    } else {
        cout<<"Error open metasector"<<endl;
        return;
    }

    metaSector.close();
    sector.close();
    // creamos el nuevo texto
    int nuevaLongitud = lenBuffer - (puntoFinal - puntoInicio + 1);
    int desplazamiento = puntoFinal - puntoInicio + 1;

    for (int i = puntoInicio; i <= nuevaLongitud; ++i) {
        buffer[i] = buffer[i + desplazamiento];
    }

    // ahora el buffer tiene el registro eliminado
    buffer[nuevaLongitud] = '\0';

    // abrimos el sector en modo escritura
    ofstream sectorWrite("./Disk/data/sectors/" + to_string(sectorSelected));
    // reescribios el sector
    sectorWrite<<buffer;
    // habrá un campo más en free space
    freeSpace[sectorSelected]--;

    /*
        procedermos a elimnar la linea de la metadata
    */
    metaSector.open("./Disk/data/meta/sectors/" + to_string(sectorSelected));
    
    ofstream temp("./Disk/data/meta/sectors/temp");
    
    if(metaSector.is_open()) {
        int row = 0;
        while (metaSector.getline(auxBuffer, lenBuffer))
        {
            if(row != posId) {
                temp<<auxBuffer;
                temp<<endl;
            }
            row++;
        }
    } else {
        cout<<"Error open meta file"<<endl;
        return;
    } 

    metaSector.close();
    temp.close();

    remove(("./Disk/data/meta/sectors/" + to_string(sectorSelected)).c_str());
    rename("./Disk/data/meta/sectors/temp", ("./Disk/data/meta/sectors/" + to_string(sectorSelected)).c_str());

    delete auxBuffer;

}   