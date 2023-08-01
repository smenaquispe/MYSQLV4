#ifndef DISK_H
#define DISK_H

#include<fstream>
#include"direct.h"
#include"../File/File.h"
#include"../Utils/btree.h"

class Disk
{
public:
 
    BTree * tree;

    int numTotalSectores;

    int lenBuffer;
    char * buffer;

    File * file;
    // sirvirá para metadata
    int NUMBER_REGISTER_PER_SECTOR = 5;
    int numPlatos;
    int numPistas;
    int numSectores;

    // numero de bytes de los registro

    // constructor que involucra un file
    Disk(File * f, int numPlatos, int numPistas, int numSectores, int sizeSector) {
        
        tree = new BTree(4);

        this->file = f;

        this->numPlatos = numPlatos;
        this->numPistas = numPistas;
        this->numSectores = numSectores;
        this->NUMBER_REGISTER_PER_SECTOR = sizeSector;
        
        buffer = new char[file->totalRegisterBytes]; // el buffer tendra el tamaño para almacenar un registro   
        this->lenBuffer = file->totalRegisterBytes;
    }

    // constructor que no necesita de un file
    // cuando la lectura del csv ya fue hecha
    Disk(int numPlatos, int numPistas, int numSectores, int sizeSector) {
        
        tree = new BTree(4);

        this->numPlatos = numPlatos;
        this->numPistas = numPistas;
        this->numSectores = numSectores;
        this->NUMBER_REGISTER_PER_SECTOR = sizeSector;

        
        ifstream infoFile("./Disk/data/meta/info_file");    

        int registerBytes;
        infoFile >> registerBytes;
        infoFile >> registerBytes;

        buffer = new char[registerBytes];
        this->lenBuffer = registerBytes;

    }


    ~Disk(){
        delete buffer;
    }

    void loadFile();
    
    // esta funcion se ejecuta para guardar toda la metadata que se necesita para volver a leer
    void saveFile();

    // funcion que desliga totalmente del file
    void run();
};

#include"loadFile.h"
#include"saveFile.h"
#include"run.h"

#endif