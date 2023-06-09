#include"BufferManager.h"

void BufferManager::printSector(int numberSector) {
    Page * currentPage;
    for(int i = 0; i < countPages; i++) {
        currentPage = getPage(i); 
        if(numberSector >= currentPage->l1 && numberSector <= currentPage->l2) {
            break;    
        }
    }
   
    currentPage->printSector(numberSector);
}