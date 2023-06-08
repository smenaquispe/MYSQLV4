#include"BufferManager.h"


void BufferManager::uploadPage(int l1, int l2) {
    Page * p = new Page(l1, l2);

    pages[countPages++] = *p;
}