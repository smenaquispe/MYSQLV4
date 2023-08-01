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


    ifstream directory("./Disk/data/meta/directory");
    string line;

    bool isFirst = true;

    while (getline(directory, line))
    {
        char * sLine;
        strcpy(sLine, line.c_str());

        char * token = myStrtok(sLine, " ");

        bool isSector = true;
        int numSector;

        while (token != nullptr)
        {
            int number = atoi(token);

            if(number || isFirst) {

                if(!isSector) {
                    tree->insert({number, numSector});
                }
        
                else {
                    numSector = number;
                    isSector = false;
                }

                isFirst = false;
            }


            token = myStrtok(nullptr, " ");
        }
        
    }

}