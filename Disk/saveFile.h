#include"Disk.h"

void Disk::saveFile() {
    ofstream metaData("./Disk/data/meta/info_file");
    
    /*
        se guardará lo siguiente:
        - numero de columnas
        - total de bytes por registro (maximo)
        - numero de registros
    */

    metaData<<this->file->numberColumns<<endl;
    metaData<<this->file->totalRegisterBytes<<endl;
    metaData<<this->file->numberRegisters<<endl;
    
}