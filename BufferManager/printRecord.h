#include"BufferManager.h"

void BufferManager::printRecord(int idRecord) {

    Index * index = disk->tree->search({idRecord, 0});
    if(!index) return;

    int numBloque = index->sect / this->NUMBER_SECTORS_PER_CLUSTER;

    // caso se encuentre en seleccionables
    int j = 0;
    for(bool b : seleccionables) {
        if(b) {
            if(pages[j].numeroBloque == numBloque) {
                pages[j].printRecord(idRecord);
                pages[j].pinCount++;
                return;
            }
        } 
        j++;
    }    

    // caso tengamos que subir una pagina
    int pos = uploadPage(numBloque);
    // digamos que el frame(pages) tiene paginas
    if(pages[pos].printRecord(idRecord)) {
        pages[pos].pinCount++;
        return;
    }   
}