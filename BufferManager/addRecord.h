#include"BufferManager.h"


void BufferManager::addRecord() {
    Page * currentPage;
    for(int i = 0; i < countPages; i++) {
        currentPage = getPage(i); 
        if(currentPage->hasSpace()) {
            break;    
        }
    }

    currentPage->addRecord();
    currentPage->printSector();
}