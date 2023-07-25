#include"Page.h"

int Page::printInfoRecord(int idRecord) {
    
    auto it = data.find(idRecord);
    
    // no se encontró
    if(it == data.end()) {
        return 0;
    }

    
    int numeroSector;
    for(auto it = sectores.begin(); it != sectores.end(); it++) {
       for(int t : it->second) {
        if(t == idRecord) {
            numeroSector = it->first;
            break;
        }
       }
    }

    cout<<"El record de id: "<<idRecord<<endl;
    cout<<"Se encuentra en el sector: "<<numeroSector<<endl;
    cout<<"Se encuentra en la pista: "<<numPista<<endl;
    cout<<"Se encuentra en la superficie: "<<numSuperficie<<endl;
    cout<<"Se encuentra en el plato: "<<numPlato<<endl;
    

    return 1;
}