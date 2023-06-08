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

        ofstream metaSector;
        ofstream sector;
        
        sector.open("./Disk/data/sectors/" + to_string(numTotalSectores));
        metaSector.open("./Disk/data/meta/sectors/" + to_string(numTotalSectores));


        while (true)
        {
            f.seekg(posicionInicio, std::ios::beg);  // Establecer la posición de lectura
            f.read(buffer, file->totalRegisterBytes);  // Leer el segmento en el buffer
            
            if(f.eof()) break;

            // necesarios para alamacenar informacion de como limitan las columnas de tamaño variable
            int column = 0;
            int acumulateColumn = file->columnBytes[0];
            bool band = false;


            for(int i = 0; i < file->totalRegisterBytes; i++) {
 
                if(buffer[i] != ' ' && !band){
                    metaSector<<i<<" ";
                    band = true;
                    //sector.write(&buffer[i], 1);
                }
                
                
                if(i == acumulateColumn) {
                    if(buffer[i] != ' ')
                        sector.write(&buffer[i], 1);
                    metaSector<<i<<" , ";
                    acumulateColumn += file->columnBytes[++column];
                    band = false;
                }

                if(band){
                    sector.write(&buffer[i], 1);
                }                              
            }      

            metaSector<<endl;
            contadorRegistros++;

            if(contadorRegistros == this->NUMBER_REGISTER_PER_SECTOR) {
                contadorRegistros = 0;
                sector.close(); 
                metaSector.close();
 
                this->numTotalSectores++;
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
    } else {
        cout<<"No se pudo abrir el archivo file"<<endl;
    }

}

#endif