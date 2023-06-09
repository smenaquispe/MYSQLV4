#include"BufferManager.h"

Page * BufferManager::getPage(int numPage) {
    return &pages[numPage];
}