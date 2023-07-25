#include"BufferManager.h"

void BufferManager::printPage(int numPage) {

    int j = 0;
    for(bool b : seleccionables) {
        if(b) {
            if(tagPages[j] == numPage) {
                pages[j].pinCount++;
                pages[j].printSector();
                return;
            }
        } 
        j++;
    }    


    for(int i = 0; i <= disk->numTotalSectores / this->NUMBER_SECTORS_PER_CLUSTER ; i++) {

        //cout<<i<<endl;        
        int pos = uploadPage(i);
        // digamos que el frame(pages) tiene paginas
        
        if(tagPages[pos] == numPage) {
            pages[pos].pinCount++;
            pages[pos].printSector();
            return;
        }    
    }   
}