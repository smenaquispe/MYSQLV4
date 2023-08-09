#include"BufferManager.h"

void BufferManager::printInfoBloque(int numeroBloque) {
    int numeroPagina = uploadPage(numeroBloque);

    if(numeroPagina == -1) {
        cout<<"No existe bloque numero: "<<numeroBloque<<endl;
        return;
    }

    map<int, vector<int>> * sectores = &pages[numeroPagina].sectores;

    for(const auto& pair: *sectores) {
        pages[numeroPagina].printInfoSector(pair.first);
    }
  
}