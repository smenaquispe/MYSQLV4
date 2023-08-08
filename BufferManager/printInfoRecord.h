#include"BufferManager.h"


void BufferManager::printInfoRecord(int idRecord) {
    
    
    Index * index = disk->tree->search({idRecord, 0});

    int numBloque = index->sect / this->NUMBER_SECTORS_PER_CLUSTER;


    int j = 0;
    for(bool b : seleccionables) {
        if(b) {
            if(pages[j].numeroBloque == numBloque) {
                cout<<"Se encuentra en el bloque: "<<numBloque<<endl;
                pages[j].printInfoRecord(idRecord);
                pages[j].pinCount++;
                return;
            }
        } 
        j++;
    }    

    int pos = uploadPage(numBloque);
    // digamos que el frame(pages) tiene paginas

    cout<<"Se encuentra en el bloque: ";
    if(pages[pos].printInfoRecord(idRecord)) {    
        //cout<<tagPages[pos]<<endl;
        pages[pos].pinCount++;
        return;
    }    

}