#include"Page.h"

void Page::deleteRecord(int idRecord) {
    // hallo en que sector se encuentra el record

    int numeroSector;

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

    sectores[numeroSector].erase(sectores[numeroSector].begin() + i);

    // eliminar todo el registro dentro de data
    data.erase(idRecord);
    freeSpace[numeroSector]--;
    cambio--;
}   