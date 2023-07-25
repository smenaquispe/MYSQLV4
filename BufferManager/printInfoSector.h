#include"BufferManager.h"

void BufferManager::printInfoSector(int numberSector) {

    int j = 0;
    for(bool b : seleccionables) {
        if(b) {
            if(pages[j].printSector(numberSector)) {
                pages[j].pinCount++;
                return;
            }
        } 
        j++;
    }    


    for(int i = 0; i <= disk->numTotalSectores / this->NUMBER_SECTORS_PER_CLUSTER ; i++) {

        //cout<<i<<endl;        
        int pos = uploadPage(i);
        // digamos que el frame(pages) tiene paginas
        
        if(pages[pos].printInfoSector(numberSector)) {
            pages[pos].pinCount++;
            return;
        }    
    }   

}