#include"BufferManager.h"

void BufferManager::deleteRecord(int numberRecord) {
    int sector = findRecord(numberRecord);
    if(sector == -1) return;

    Page * currentPage;
    for(int i = 0; i < countPages; i++) {
        currentPage = getPage(i); 
        if(sector >= currentPage->l1 && sector <= currentPage->l2) {
            break;    
        }
    }

    currentPage->deleteRecord(numberRecord);
    currentPage->printSector(sector);
}