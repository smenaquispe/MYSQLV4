#include"Page.h"

void Page::loadData() {
    for(int i = l1; i <= l2; i++) {
        loadData(i);
    }
}

void Page::loadData(int numeroSector) {
    ifstream sector("./Disk/data/sectors/" + to_string(numeroSector));
    ifstream metaSector("./Disk/data/meta/sectors/" + to_string(numeroSector));

    int lenBuffer = 1024;

    char buffer[lenBuffer];
    char auxBuffer[lenBuffer];

    sector.getline(auxBuffer, 1024);
    sector.read(auxBuffer, 1024);

    bool isId = true;

    int id;
    string dataStr;

    if(metaSector.is_open()) {
        int pos = 0;
        while (metaSector.getline(buffer, lenBuffer))
        {
            char * token = myStrtok(buffer, " ");
            int a, b;
            bool first = true;

            while (token != nullptr)
            {
                if(strcmp(token, ",") && first) {
                    a = atoi(token);
                    first = false;
                }

                else if(strcmp(token, ",") && !first) {
                    b = atoi(token);
                    first = true;
                }

                // caso solo un numero
                else if(!strcmp(token, ",") && !first) {
                    b = a;
                    first = true;
                    
                    dataStr = string(auxBuffer + pos, 1);
                    data[id].push_back(dataStr);
                    
                    //cout<<pos<<endl;
                    pos += 1;
                }

                else if(!strcmp(token, ",") && first) {
                    if((b - a) == 0){
                        first = true;
                        dataStr = string(auxBuffer + pos, 1);
                        data[id].push_back(dataStr);

                        //cout<<pos<<endl;
                        pos += 1;
                    } else {
                        dataStr = string(auxBuffer + pos, b - a);

                        if(isId) {
                            id = stoi(dataStr);
                            vector<string> a;
                            data[id] = a;
                            isId = false;
    
                        } else {
                            data[id].push_back(dataStr);
                        }

                        //cout<<pos<<endl;
                        pos += b - a;
                    }
                }

                token = myStrtok(nullptr, " ");
            } 

            isId = true;
        }
        
    } else {
        cout<<"Problems open meta sector file"<<endl;
        return;
    }

} 