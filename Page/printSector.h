#include"Page.h"
#include"../Utils/myStrtok.h"

void Page::printSector() {
    for(int i = l1; i <= l2; i++) {
        printSector(i);
    }    
}

void Page::printSector(int numberSector) {
    /*
        provicional:
            la idea es que el buffermanager levante una pagina  
            y a traves de esta pagina podamos imprimir los sectores
    */
    ifstream sector("./Disk/data/sectors/" + to_string(numberSector));
    ifstream metaSector("./Disk/data/meta/sectors/" + to_string(numberSector));

    char * auxBuffer = new char[1024];

    sector.getline(auxBuffer, 1024);
    sector.read(auxBuffer, 1024);

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
                    cout.write(auxBuffer + pos, 1);
                    cout<<" ";

                    //cout<<pos<<endl;
                    pos += 1;
                }

                else if(!strcmp(token, ",") && first) {
                    if((b - a) == 0){
                        first = true;
                        cout.write(auxBuffer + pos, 1);
                        cout<<" ";

                        //cout<<pos<<endl;
                        pos += 1;
                    } else {
                        cout.write(auxBuffer + pos, b - a);
                        cout<<" ";
                        
                        //cout<<pos<<endl;
                        pos += b - a;
                    }
                }


                token = myStrtok(nullptr, " ");
            } 

            cout<<endl;
        }
        
    } else {
        cout<<"Problems open meta sector file"<<endl;
        return;
    }

    delete auxBuffer;
}