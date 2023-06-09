#include"BufferManager.h"


void BufferManager::uploadPage(int l1, int l2) {
    Page * p = new Page(l1, l2, NUMBER_REGISTER_PER_SECTOR);

    pages[countPages++] = *p;
}