#include"Page.h"

void Page::printRecord(int idRecord) {
    int sectorSelected = this->findRecord(idRecord);
    if(sectorSelected == -1) return;
    
    ifstream sector("./Disk/data/sectors/" + to_string(sectorSelected));
    ifstream metaSector("./Disk/data/meta/sectors/" + to_string(sectorSelected));

    char * auxBuffer = new char[1024];

    sector.getline(auxBuffer, 1024);
    sector.read(auxBuffer, 1024);

    if(metaSector.is_open()) {
        int pos = 0;
        
        bool isId = false;


        while (metaSector.getline(buffer, lenBuffer))
        {
            char * token = myStrtok(buffer, " ");
            int a, b;
            bool first = true;
            bool band = true;
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
                    
                    if(isId){
                        cout.write(auxBuffer + pos, 1);
                        cout<<" ";

                    }

                    //cout<<pos<<endl;
                    pos += 1;
                }

                else if(!strcmp(token, ",") && first) {
                    if((b - a) == 0){
                        first = true;

                        if(isId) {
                            cout.write(auxBuffer + pos, 1);
                            cout<<" ";

                        }

                        //cout<<pos<<endl;
                        pos += 1;
                    } else {
                        
                        
                        if(band) {
                            string numberString(auxBuffer + pos, b - a);
                            int id = stoi(numberString);
                            if(id == idRecord) {
                                isId = true;
                            }
                            band = false;
                        }

                        if(isId) {
                            cout.write(auxBuffer + pos, b - a);
                            cout<<" ";
                        }
                        
                        //cout<<pos<<endl;
                        pos += b - a;
                    }
                }

                token = myStrtok(nullptr, " ");
            } 
            
            if(isId) break;

        }
        
    } else {
        cout<<"Problems open meta sector file"<<endl;
        return;
    }

    delete auxBuffer;
}