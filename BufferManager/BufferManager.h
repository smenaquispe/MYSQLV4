#ifndef BUFFER_MANAGER_H
#define BUFFER_MANAGER_H

#include"../Page/Page.h"
#include"../Disk/Disk.h"
#include"../Utils/myStrtok.h"

#include<vector>
using namespace std;

class BufferManager
{
public:

    Page * pages;
    Disk * disk;
    int lenPages;
    int countPages;

    char * buffer;
    int lenBuffer = 1024;

    int NUMBER_REGISTER_PER_SECTOR;
    int NUMBER_SECTORS_PER_CLUSTER;

    BufferManager(Disk * d, int a, int cluserSize) {

        this->disk = d;
        this->NUMBER_SECTORS_PER_CLUSTER = cluserSize;

        lenPages = d->numTotalSectores / this->NUMBER_SECTORS_PER_CLUSTER;
        
        this->lenPages = a;
        pages = new Page[lenPages];
        
        
        countPages = 0;

        buffer = new char[lenBuffer];
        
        this->NUMBER_REGISTER_PER_SECTOR = d->NUMBER_REGISTER_PER_SECTOR;
        
    }

    ~BufferManager() {
        delete [] buffer;
    }

    void uploadPage(int l1, int l2, int n, int p, int q);
    void uploadAllPages();
    Page * getPage(int numPage);
    void printPage(int numPage);
    void deletePage(int numPage);
    int findRecord(int numberRecord);
};

#include"getPage.h"
#include"uploadPage.h"
#include"deletePage.h"
#include"printPage.h"
#include"findRecord.h"
#include"uploadAllPages.h"

#endif