#ifndef PAGE_H
#define PAGE_H

#include<fstream>
#include<iostream>
#include<map>
#include<vector>
#include<cstring>

#include"../Utils/infoSector.h"

using namespace std;

class Page
{
public:
    int l1, l2; // parte del sector l1 al l2
    map<int, int> freeSpace; // alamcena cuales son los sectores que tienen espacio libre

    int maximumSector; // lo que mide maximo el sector para tener un buffer

    // a continuacion metadata de donde puede ubicarse este bloque(pagina)
    int numPlato; // el plato donde se encuentra
    int numSuperficie; // si es que este bloque se encuentra en las 2 superficies
    int numPista;  // las pistas que ocupa

    // será una estructura de datos
    // un hash, que apunta a un vector
    map<int, vector<string>> data; // esta es la informacion que la pagina levanta en memoria
    // sectores y los registros que guarda
    map<int, vector<int>> sectores;
    vector<InfoSectores> infoSectores;

    // el cambio en cuanto a records
    int cambio = 0;

    // numero de bloque que representa la pagina
    int numeroBloque;

    // bits
    bool dirtyBit = 0; // detecta si hubo un cambio
    int pinCount = 0; // cuantas veces esta siendo usado la pagina

    Page() {
    }

    Page(int numeroBloque, int l1, int l2, int maximumSector, vector<InfoSectores> infoSectores) {
        
        this->l1 = l1;
        this->l2 = l2;
        this->maximumSector = maximumSector;

        this->numeroBloque = numeroBloque;

        this->infoSectores = infoSectores;

        loadMeta();
        loadData();
    }
    ~Page() {}

    void printSector();
    int printSector(int numberSector);
    int findRecord(int idRecord);
    void loadMeta();
    vector<int> addRecord();
    int deleteRecord(int idRecord);
    bool hasSpace();
    void printInfo();
    int printInfoSector(int numberSector);
    void printSize();
    void printSizeSector(int numberSector);

    int printRecord(int idRecord);

    int getSize();

    // load data, permitirá subir toda la informacion guardado en sectores a memoria (string)
    void loadData();
    void loadData(int numeroSector);

    // funcion que permitirá guardar los cambios en disco
    void saveSectors(Disk * disk);

    // imprimir informaciion de un solo record
    int printInfoRecord(int idRecord);
};


#include"printSector.h"
#include"findRecord.h"
#include"loadMeta.h"
#include"addRecord.h"
#include"hasSpace.h"
#include"deleteRecord.h"
#include"printInfo.h"
#include"printSize.h"
#include"printSizeSector.h"
#include"printInfoSector.h"
#include"printRecord.h"
#include"getSize.h"

#include"loadData.h"
#include"saveSectors.h"
#include"printInfoRecord.h"

#endif