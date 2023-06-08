#include"BufferManager.h"

void BufferManager::deletePage(int numberPage) {
    Page * findPage = &pages[numberPage];
    delete findPage;
}