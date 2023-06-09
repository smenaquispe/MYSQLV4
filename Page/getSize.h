#include"Page.h"

int Page::getSize() {
    int tamanoTotal = 0;
    for(int i = l1; i <= l2; i++) {
        ifstream sector("./Disk/data/sectors/" + to_string(i));
        sector.seekg(0, ios::end); // Coloca el puntero al final del archivo
        streampos tamano = sector.tellg(); // Obtiene la posición actual del puntero, que es el tamaño del archivo
        sector.close();
        tamanoTotal += tamano;
    }

    return tamanoTotal;
}