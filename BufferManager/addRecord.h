#include"BufferManager.h"


void BufferManager::addRecord() {
    int j = 0;
    
    for(bool b : seleccionables) {
        if(b) {
            cout<<j<<endl;
            vector<int> data = pages[j].addRecord();
            int numeroSector = data[0];
            if(numeroSector != -1) {
                cout<<"Fue agregado en el bloque: "<<tagPages[j]<<endl;
                pages[j].pinCount++;
                pages[j].dirtyBit = 1;
                disk->tree->insert({data[1], numeroSector});
                return;
            }
        } 
        j++;
    }    


    for(int i = 0; i <= disk->numTotalSectores / this->NUMBER_SECTORS_PER_CLUSTER ; i++) {

        //cout<<i<<endl;  
        int pos = uploadPage(i);
        // digamos que el frame(pages) tiene paginas

        vector<int> data = pages[pos].addRecord();
        int numeroSector = data[0];
        if(numeroSector != -1) {
            cout<<"Fue agregado en el bloque: "<<tagPages[pos]<<endl;
            pages[pos].pinCount++;
            pages[pos].dirtyBit = 1;
            disk->tree->insert({data[1], numeroSector});
            return;
        }    
    }   

}