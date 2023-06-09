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

    int maximumSector; // lo que mide maximo el sector para tener un buffer

    // a continuacion metadata de donde puede ubicarse este bloque(pagina)
    int numPlato; // el plato donde se encuentra
    int numSuperficie; // si es que este bloque se encuentra en las 2 superficies
    int numPista;  // las pistas que ocupa

    Page() {
    }

    Page(int l1, int l2, int maximumSector, int n, int p, int q) {
        this->l1 = l1;
        this->l2 = l2;
        this->maximumSector = maximumSector;
        buffer = new char[lenBuffer];

        // seteamos la informacion de donde se ubica el bloque
        this->numPlato = n;
        this->numSuperficie = p;
        this->numPista = q;

        loadMeta();
    }
    ~Page() { 
        delete [] buffer;
    }

    void printSector();
    void printSector(int numberSector);
    int findRecord(int idRecord);
    void loadMeta();
    void addRecord();
    void deleteRecord(int idRecord);
    bool hasSpace();
    void printInfo();
};


#include"printSector.h"
#include"findRecord.h"
#include"loadMeta.h"
#include"addRecord.h"
#include"hasSpace.h"
#include"deleteRecord.h"
#include"printInfo.h"

#endif