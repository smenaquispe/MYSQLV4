#ifndef BUFFER_MANAGER_H
#define BUFFER_MANAGER_H

#include"../Page/Page.h"

using namespace std;

class BufferManager
{
public:

    Page * pages;
    int lenPages;
    int countPages;

    int NUMBER_REGISTER_PER_SECTOR;

    BufferManager(int lenPages, int sectorLength) {
        pages = new Page[lenPages];
        this->lenPages = lenPages;
        countPages = 0;

        this->NUMBER_REGISTER_PER_SECTOR = sectorLength;
    }

    ~BufferManager() {}

    void uploadPage(int l1, int l2);
    Page * getPage(int numPage);
    void printPage(int numPage);
    void deletePage(int numPage);
};

#include"getPage.h"
#include"uploadPage.h"
#include"deletePage.h"
#include"printPage.h"

#endif