#include"BufferManager.h"

void BufferManager::getPage(int numPage) {
    pages[numPage].printSector();
}