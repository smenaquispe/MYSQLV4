#include"BufferManager.h"


void BufferManager::addRecord() {
    int j = 0;
    for(bool b : seleccionables) {
        if(b) {
            if(pages[j].addRecord()) {
                cout<<"Fue agregado en el bloque: "<<tagPages[j]<<endl;
                pages[j].pinCount++;
                pages[j].dirtyBit = 1;
                return;
            }
        } 
        j++;
    }    


    for(int i = 0; i <= disk->numTotalSectores / this->NUMBER_SECTORS_PER_CLUSTER ; i++) {

        //cout<<i<<endl;        
        int pos = uploadPage(i);
        // digamos que el frame(pages) tiene paginas
        
        if(pages[pos].addRecord()) {
            cout<<"Fue agregado en el bloque: "<<tagPages[pos]<<endl;
            pages[pos].pinCount++;
            pages[j].dirtyBit = 0;
            return;
        }    
    }   

}