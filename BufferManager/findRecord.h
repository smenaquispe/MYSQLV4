#include"BufferManager.h"

int BufferManager::findRecord(int numberRecord) {
    ifstream directory("./Disk/data/meta/directory");

    if(directory.is_open()) {

        while (directory.getline(buffer, lenBuffer))
        {
            bool first = true;
            char * token = myStrtok(buffer, " ");
            int sector = atoi(token);

            while (token != nullptr)
            {
                if(!first) {
                    if(atoi(token) == numberRecord) {
                        return sector;                       
                    }                    
                }

                if(first) first = false;
                token = myStrtok(nullptr, " ");
            }           
        }
        directory.close();
    } else {
        cout<<"Error open directory"<<endl;
        return -1;
    }

    return -1;
}