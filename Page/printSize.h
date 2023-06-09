#include"Page.h"

void Page::printSize() {

    long int tamanoTotal = 0;
    for(int i = l1; i <= l2; i++) {
        ifstream sector("./Disk/data/sectors/" + to_string(i));
        sector.seekg(0, ios::end); // Coloca el puntero al final del archivo
        streampos tamano = sector.tellg(); // Obtiene la posición actual del puntero, que es el tamaño del archivo
        sector.close();
        tamanoTotal += tamano;
    }
    

    cout<<"El tamano total del bloque es: "<<tamanoTotal<<" bytes"<<endl;
}