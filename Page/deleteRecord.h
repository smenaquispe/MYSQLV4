#include"Page.h"

void Page::deleteRecord(int idRecord) {
    // hallo en que sector se encuentra el record

    int numeroSector;

    for(auto it = sectores.begin(); it != sectores.end(); ++it) {
        vector<int> temp = it->second;
        
        int i = 0;
        for(i = 0; i < temp.size(); i++) {
            if(temp[i] == idRecord) { // se encontro el record en este sector
                numeroSector = it->first;
                break;          
            }
        }

        // eliminar el numero de record en sectores
        it->second.erase(it->second.begin() + i);

    }

    // eliminar todo el registro dentro de data
    data.erase(idRecord);
    freeSpace[numeroSector]--;
}   