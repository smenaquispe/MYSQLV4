#include"BufferManager.h"

void BufferManager::deleteRecord(int idRecord) {
    
    int j = 0;
    for(bool b : seleccionables) {
        if(b) {
            if(pages[j].deleteRecord(idRecord)) {
                cout<<"Fue eliminado en el bloque: "<<tagPages[j]<<endl;
                pages[j].pinCount++;
                pages[j].dirtyBit = 1;
                return;
            }
        } 
        j++;
    }    

    Index * index = disk->tree->search({idRecord, 0});
    if(!index) return;

    int numBloque = index->sect / this->NUMBER_SECTORS_PER_CLUSTER;

    int pos = uploadPage(numBloque);
        // digamos que el frame(pages) tiene paginas

    if(pages[pos].deleteRecord(idRecord)) {
        cout<<"Fue eliminado en el bloque: "<<tagPages[pos]<<endl;
        pages[pos].pinCount++;
        pages[pos].dirtyBit = 1;
        
        disk->tree->remove({idRecord, 0});

        return;
    }    
        
}