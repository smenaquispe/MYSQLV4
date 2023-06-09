#ifndef PAGE_H
#define PAGE_H

#include<fstream>
#include<iostream>
#include<map>

using namespace std;

class Page
{
public:
    int l1, l2;
    char * buffer;
    int lenBuffer = 1024;
    map<int, int> freeSpace; // alamcena cuales son los sectores que tienen espacio libre

    Page() {}

    Page(int l1, int l2) {
        this->l1 = l1;
        this->l2 = l2;
        buffer = new char[lenBuffer];
    }
    ~Page() { 
        delete buffer;
    }

    void printSector();
    void printSector(int numberSector);
    void findRecord(int idRecord);
    void loadMeta();
};


#include"printSector.h"
#include"findRecord.h"
#include"loadMeta.h"

#endif