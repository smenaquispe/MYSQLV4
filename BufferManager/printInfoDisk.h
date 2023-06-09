#include"BufferManager.h"

void BufferManager::printInfoDisk() {

    long int tamanoTotal = 0;
    for(int i = 1; i <= disk->numPlatos; i++) {
        long int tamano = 0;
        for(int j = 0; j < lenPages; j++) {
            if(pages[j].numPlato == i) {
                tamano += pages[j].getSize();
            }
        }

        cout<<"Tamano en plato: "<<i<<": "<<tamano<<endl;
        tamanoTotal += tamano;
    }

    cout<<"Tamano total del disco: "<<tamanoTotal<<endl;
}