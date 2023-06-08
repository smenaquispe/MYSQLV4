#ifndef DISK_H
#define DISK_H

#include<fstream>
#include"../File/File.h"

class Disk
{
public:

    File * file;
    int numTotalSectores;
    int NUMBER_REGISTER_PER_SECTOR = 5;
    int lenBuffer;
    char * buffer;

    Disk(File * f) {
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