#include"Page.h"

int Page::deleteRecord(int idRecord) {
    // hallo en que sector se encuentra el record

    int numeroSector = -1;

    int i = 0;
    for(auto it = sectores.begin(); it != sectores.end(); ++it) {
        vector<int> temp = it->second;
        
        for(i = 0; i < temp.size(); i++) {
            if(temp[i] == idRecord) { // se encontro el record en este sector
                numeroSector = it->first;
                break;          
            }
        }
    }

    if(numeroSector == -1) {
        return 0;
    }

    cout<<"Fue eliminado en el sector: "<<numeroSector<<endl;

    //sectores[numeroSector].erase(sectores[numeroSector].begin() + i);
    vector<int> temp = sectores[numeroSector];
    vector<int> aux;

    for(int t : temp) {
        if(t != idRecord) {
            aux.push_back(t);
        }
    }

    sectores[numeroSector] = aux;


    // eliminar todo el registro dentro de data
    data.erase(idRecord);
    freeSpace[numeroSector]--;
    cambio--;

    return 1;
}   