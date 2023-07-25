#include"BufferManager.h"

void BufferManager::printAll() {
    
    ifstream info_file("./Disk/data/meta/info_file");

    int numeroRegistros;
    info_file >> numeroRegistros;
    info_file >> numeroRegistros;
    info_file >> numeroRegistros;
   
    for(int i = 1; i <= numeroRegistros; i++) {
        printRecord(i);
    }
}