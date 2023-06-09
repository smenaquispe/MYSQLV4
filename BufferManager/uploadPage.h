#include"BufferManager.h"


void BufferManager::uploadPage(int l1, int l2, int n, int p, int q) {
    Page * page = new Page(l1, l2, NUMBER_REGISTER_PER_SECTOR, n, p , q);

    pages[countPages++] = *page;
}