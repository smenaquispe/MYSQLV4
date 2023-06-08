#ifndef PAGE_H
#define PAGE_H

#include<fstream>
#include<iostream>

using namespace std;

class Page
{
public:
    int l1, l2;
    char * buffer;
    int lenBuffer = 1024;

    Page(int l1, int l2) : l1(l1), l2(l2) {
        buffer = new char[lenBuffer];
    }
    ~Page() { 
        delete buffer;
    }

    void printSector();
    void printSector(int numberSector);

};

#include"printSector.h"

#endif