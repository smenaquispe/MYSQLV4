#include "BufferManager.h"

void BufferManager::mostrarBufferPool() {

    long int total = 0;

    for(int i = 0; i < lenPages; i++) {
        if(seleccionables[i]) {
            cout<<"Pagina nro. "<<i<<" esta lleno"<<endl;
            cout<<"Se encuentra el bloque nro. "<<pages[i].numeroBloque<<endl;

            cout<<"Pin count de la pagina es: "<<pages[i].pinCount<<endl;
            
            if(pages[i].dirtyBit) {
                cout<<"Se realizaron cambios sin guardar en esta pagina"<<endl;
            } else{
                cout<<"No hay cambios"<<endl;
            }

            int size = pages[i].getSize();
            total += size;
            cout<<"Capacidad ocupada: "<<size<<" bytes"<<endl;;
        
        } else {
            cout<<"Pagina nro. "<<i<<" esta vacio"<<endl;
        }
    }   

    cout<<"Total ocupado: "<<total<<endl;
}