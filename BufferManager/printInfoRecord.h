#include"BufferManager.h"


void BufferManager::printInfoRecord(int idRecord) {
    
    int j = 0;
    for(bool b : seleccionables) {
        if(b) {
            if(pages[j].printRecord(idRecord)) {
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

        if(pages[pos].printInfoRecord(idRecord)) {    
            cout<<"Se encuentra en el bloque: ";
            cout<<tagPages[pos]<<endl;
            pages[pos].pinCount++;
            return;
        }    
    }   

}