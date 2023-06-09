#include"BufferManager.h"

void BufferManager::printPage(int numPage) {
    pages[numPage].printSector();
}