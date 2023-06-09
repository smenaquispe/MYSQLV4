#ifndef BUFFER_MANAGER_H
#define BUFFER_MANAGER_H

#include"../Page/Page.h"
#include"../Disk/Disk.h"
#include"../Utils/myStrtok.h"

#include<vector>
using namespace std;

struct Node {
    int firstRecord;
    int lastRecord;
    int sector;
};

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

    vector<Node> recordTrack;

    BufferManager(int lenPages, Disk * disk) {
        
        lenPages = disk->numTotalSectores / this->NUMBER_SECTORS_PER_CLUSTER;
        
        pages = new Page[lenPages];
        this->lenPages = lenPages;
        
        countPages = 0;

        buffer = new char[lenBuffer];
        
        this->NUMBER_REGISTER_PER_SECTOR = disk->NUMBER_REGISTER_PER_SECTOR;
    }

    ~BufferManager() {
        delete [] buffer;
    }

    void uploadPage(int l1, int l2);
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

#endif