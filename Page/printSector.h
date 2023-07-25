#include"Page.h"
#include"../Utils/myStrtok.h"

void Page::printSector() {
    for(auto it = data.begin(); it != data.end(); ++it) {
        cout<<it->first<<" ";
        for(int i = 0; i < it->second.size(); i++) 
            cout<<it->second[i]<<" ";
        cout<<endl;
    }
}

void Page::printSector(int numberSector) {
    // el sector no se encuentra en la pagina
    if(!(l1 <= numberSector && l2 >= numberSector)) {
        return;
    }

    vector<int> temp = sectores[numberSector];
    for(int idRecord : temp) {
        printRecord(idRecord);
    }
    
}