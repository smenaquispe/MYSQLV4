#include"BufferManager.h"


void BufferManager::printInfoRecord(int idRecord) {
    

    Index * index = disk->tree->search({idRecord, 0});
    if(!index) return;

    int numBloque = index->sect / this->NUMBER_SECTORS_PER_CLUSTER;

    // caso se encuentre en seleccionables
    int j = 0;
    for(bool b : seleccionables) {
        if(b) {
            if(pages[j].numeroBloque == numBloque) {
                pages[j].printInfoRecord(index->sect);
                pages[j].pinCount++;
                return;
            }
        } 
        j++;
    }    

    // caso tengamos que subir una pagina
    int pos = uploadPage(numBloque);
    // digamos que el frame(pages) tiene paginas
    if(pages[pos].printInfoRecord(index->sect)) {
        pages[pos].pinCount++;
        return;
    }     

}