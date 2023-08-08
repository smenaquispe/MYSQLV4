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
    char line[1024];

    bool isFirst = true;

    while (directory.getline(line, 1024))
    {
        //cout<<line<<endl;
        
        //cout<<sLine<<endl;
        char * token = myStrtok(line, " ");

        bool isSector = true;
        int numSector;

        while (token != nullptr)
        {
            int number = atoi(token);
            //cout<<number<<endl;

            if(number || isFirst) {

                if(!isSector) {
                    tree->insert({number, numSector});
                    //cout<<number<<endl;
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