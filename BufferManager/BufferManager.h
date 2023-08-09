#ifndef BUFFER_MANAGER_H
#define BUFFER_MANAGER_H

#include"../Page/Page.h"
#include"../Disk/Disk.h"
#include"../Utils/myStrtok.h"
#include"../Utils/infoSector.h"

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

    vector<int> tagPages;
    vector<int> vidaPages;
    vector<bool> seleccionables;
    int cualMeQuede = 0;

    BufferManager(Disk * d, int a, int cluserSize) {

        this->disk = d;
        this->NUMBER_SECTORS_PER_CLUSTER = cluserSize;

        lenPages = d->numTotalSectores / this->NUMBER_SECTORS_PER_CLUSTER;
        
        this->lenPages = a;
        pages = new Page[lenPages];
        
        countPages = 0;

        buffer = new char[lenBuffer];
        
        this->NUMBER_REGISTER_PER_SECTOR = d->NUMBER_REGISTER_PER_SECTOR;

        for(int i = 0; i < lenPages; i++) {
            tagPages.push_back(0);
            vidaPages.push_back(0);
            seleccionables.push_back(false);
        }
        
    }

    ~BufferManager() {
        delete [] buffer;
    }

    int uploadPage(int nbloque, int l1, int l2, vector<InfoSectores> info);
    int uploadPage(int numeroBloque);

    void uploadAllPages();
    Page * getPage(int numPage);
    void printPage(int numPage);
    void deletePage(int numPage);
    int findRecord(int numberRecord);
    void deleteRecord(int numberRecord);
    void addRecord();
    void printRecord(int idRecord);
    void printAll();
    void printInfoDisk();

    void printSector(int sector);
    void printInfoSector(int sector);

    void printInfoRecord(int numberRecord);

    void printInfoBloque(int numeroBloque);

    void save();
};

#include"getPage.h"
#include"uploadPage.h"
#include"deletePage.h"
#include"printPage.h"
#include"findRecord.h"
#include"uploadAllPages.h"
#include"addRecord.h"
#include"deleteRecord.h"
#include"printRecord.h"
#include"printAll.h"
#include"printInfoDisk.h"
#include"printSector.h"
#include"printInfoSector.h"
#include"printInfoRecord.h"
#include"save.h"
#include"printInfoBloque.h"

#endif