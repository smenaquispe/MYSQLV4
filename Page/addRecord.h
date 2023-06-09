#include"Page.h"

void Page::addRecord() {
    // abrimos el archivo que contiene informacion del nuevo registro
    fstream input("./docs/input");

    int sectorSelected;

    if(input.is_open()) {
        for (auto it = freeSpace.begin(); it != freeSpace.end(); ++it) {
            
            // se encontró el sector con espacio libre
            
            if(it->second < maximumSector) {
                sectorSelected = it->first;
                break;
            }
        }

        input.close();
    } else {
        cout<<"Problem open input file"<<endl;
    }

    // abrimos el sector que queremos modificar
    fstream sector("./Disk/data/sectors/" + to_string(sectorSelected));
    fstream metaSector("./Disk/data/meta/sectors" + to_string(sectorSelected));

    /*
        1. leer el meta y sacar donde es que tengo un espacio en blanco
        2. el meta tiene que retornar, punto inicio 
    */


}