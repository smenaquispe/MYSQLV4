#ifndef LOAD_FILE
#define LOAD_FILE

#include"Disk.h"

void Disk::loadFile() {
    // abrimos el file
    ifstream f("./docs/file");

    // cuantos bytes alamcena cada registro
    if(f.is_open()) {

        int posicionInicio = 0; // para el buffer
        int contadorRegistros = 0; // cuenta los registros quer son alamacenados en un sector
        this->numTotalSectores = 0; // cuenta el numero total de sectores que son almacenados en el disco

        ofstream metaSector; // metadata de cada sector
        ofstream sector; // file donde se almacena la informacion del sector
        ofstream directory; // directorio de metadata, sobre que registros se guardan en ciertos sectores

        sector.open("./Disk/data/sectors/" + to_string(numTotalSectores));
        metaSector.open("./Disk/data/meta/sectors/" + to_string(numTotalSectores));

        directory.open("./Disk/data/meta/directory");
        directory<<numTotalSectores<<" ";


        while (true)
        {
            f.seekg(posicionInicio, std::ios::beg);  // Establecer la posición de lectura
            f.read(buffer, file->totalRegisterBytes);  // Leer el segmento en el buffer

            if(f.eof()) break;

            // necesarios para alamacenar informacion de como limitan las columnas de tamaño variable
            int column = 0;
            int acumulateColumn = file->columnBytes[0];
            bool band = false;

            stringstream id; // guarda los ids de cada registro

            for(int i = 0; i <= file->totalRegisterBytes; i++) {
                
                if(buffer[i] != ' ' && !band){
                    metaSector<<i<<" ";
                    band = true;
                }
                
                if(i == acumulateColumn) {
                    if(buffer[i] != ' ' && i != file->totalRegisterBytes) {
                        sector.write(&buffer[i], 1);
                    }

                    metaSector<<i<<" , ";
                    acumulateColumn += file->columnBytes[++column];
                    band = false;
                    
                    // podemos guardar el id
                    if(column == 1) {
                        directory<<id.str()<<" ";
                    }
                }

                if(band){
                    if(i != file->totalRegisterBytes) {
                        sector.write(&buffer[i], 1);
                        
                        // significa que esta guardando el id
                        if(column == 0) {
                            id<<buffer[i]; 
                        }
                    }
                }                              
            }      

            metaSector<<endl;
            contadorRegistros++;

            if(contadorRegistros == this->NUMBER_REGISTER_PER_SECTOR) {
                contadorRegistros = 0;
                sector.close(); 
                metaSector.close();

                this->numTotalSectores++;
                directory<<endl<<numTotalSectores<<" ";

                sector.open("./Disk/data/sectors/" + to_string(numTotalSectores));
                metaSector.open("./Disk/data/meta/sectors/" + to_string(numTotalSectores));
            }

            int caracteresLeidos = f.gcount();  // Obtener la cantidad de caracteres leídos

            if (caracteresLeidos < file->totalRegisterBytes) {
                break;  // Si se leen menos caracteres que el tamaño del segmento, es el final del archivo o de la línea
            }

            posicionInicio += caracteresLeidos;  // Actualizar la posición de inicio para el siguiente segmento

        }
        
        f.close();
        directory.close();
    } else {
        cout<<"No se pudo abrir el archivo file"<<endl;
    }

}

#endif