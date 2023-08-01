#include"BufferManager.h"

void BufferManager::printRecord(int idRecord) {

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

    BTreeNode * n = disk->tree->search({idRecord, 0});
    Index * index = n->getIndex({idRecord, 0});

    int numBloque = index->sect / this->NUMBER_SECTORS_PER_CLUSTER;
    
    int pos = uploadPage(numBloque);
        // digamos que el frame(pages) tiene paginas
        
    if(pages[pos].printRecord(idRecord)) {
        pages[pos].pinCount++;
        return;
    }   
}