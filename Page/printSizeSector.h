#include"Page.h"

void Page::printSizeSector(int numberSector) {
    ifstream sector("./Disk/data/sectors/" + to_string(numberSector));
    sector.seekg(0, ios::end); // Coloca el puntero al final del archivo
    streampos tamano = sector.tellg(); // Obtiene la posición actual del puntero, que es el tamaño del archivo
    sector.close();

    cout<<"El sector: "<<numberSector<<" almacena un total de: "<<tamano<<" bytes"<<endl;
}