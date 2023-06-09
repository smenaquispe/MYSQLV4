#ifndef PAGE_H
#define PAGE_H

#include<fstream>
#include<iostream>
#include<map>
#include<cstring>

using namespace std;

class Page
{
public:
    int l1, l2;
    char * buffer;
    int lenBuffer = 1024;
    map<int, int> freeSpace; // alamcena cuales son los sectores que tienen espacio libre

    int maximumSector;

    Page() {}

    Page(int l1, int l2, int maximumSector) {
        this->l1 = l1;
        this->l2 = l2;
        this->maximumSector = maximumSector;
        buffer = new char[lenBuffer];
        loadMeta();
    }
    ~Page() { 
        delete buffer;
    }

    void printSector();
    void printSector(int numberSector);
    int findRecord(int idRecord);
    void loadMeta();
    void addRecord();
    void deleteRecord(int idRecord);
    bool hasSpace();
};


#include"printSector.h"
#include"findRecord.h"
#include"loadMeta.h"
#include"addRecord.h"
#include"hasSpace.h"
#include"deleteRecord.h"

#endif