#ifndef DISK_H
#define DISK_H

#include<fstream>
#include"direct.h"
#include"../File/File.h"

class Disk
{
public:

    File * file;
    
    int numTotalSectores;

    int lenBuffer;
    char * buffer;

    // sirvirá para metadata
    int NUMBER_REGISTER_PER_SECTOR = 5;
    int numPlatos;
    int numPistas;
    int numSectores;

    Disk(File * f, int numPlatos, int numPistas, int numSectores, int sizeSector) {
        
        this->numPlatos = numPlatos;
        this->numPistas = numPistas;
        this->numSectores = numSectores;
        this->NUMBER_REGISTER_PER_SECTOR = sizeSector;

        this->file = f;
        buffer = new char[file->totalRegisterBytes]; // el buffer tendra el tamaño para almacenar un registro   
        this->lenBuffer = file->totalRegisterBytes;
    }
    ~Disk(){
        delete buffer;
    }

    void loadFile();
};

#include"loadFile.h"

#endif