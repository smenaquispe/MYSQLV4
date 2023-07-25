#include<filesystem>
#include"Disk.h"


namespace fs = std::filesystem;

void Disk::run() {
    string sectorFolder = "./Disk/data/sectors";
    
    int numeroSectores = 0;

    for (const auto& entry : fs::directory_iterator(sectorFolder)) {
        if (fs::is_regular_file(entry)) {
            numeroSectores++;
        }
    }

    this->numTotalSectores = numeroSectores;

}