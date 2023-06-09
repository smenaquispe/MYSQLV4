/**
 * 
 * tener el file listo para su lectura
 * 
 * el disco tendrá sus funciones, pero los sectores serán particiones virtuales del file
 * 
 * el buffer se encargará de levantar bloques que serán usados en tiempo de ejecucion
 * 
 * 
 * 
*/

#include<iostream>
#include"File/File.h"
#include"Disk/Disk.h"
#include"Page/Page.h"
#include"BufferManager/BufferManager.h"
using namespace std;

int main() {

    File f("./titanic.csv");
    f.extractSchema();
    f.toFile();

    /*
        f -> leera el file f
        5 platos
        2 superficies (siempre)
        7 pistas
        4 -> cada pista almacena un maximo de 4 sectores
        5 -> cada sector almacena el tamaño de 5 registros
    */
    Disk d(&f, 5, 7, 4, 5);
    d.loadFile();

    // alamcena un máximo de 6 paginas
    // leerá los datos del disco d

    /*
        d -> leera el disco d
        70 -> levanta como máximo 70 paginas al mismo tiempo
        3 -> cada bloque almacena 3 sectores como maximo
    */
    BufferManager manager(&d, 70, 3);

    /*
    manager.uploadPage(106,108);
    manager.uploadPage(0, 5);
    manager.uploadPage(175,178);

    manager.getPage(1)->deleteRecord(2);
    manager.getPage(1)->deleteRecord(5);

    manager.getPage(1)->addRecord();
    manager.printPage(0);
    */

    manager.uploadAllPages();

    manager.getPage(0)->printInfo();
    manager.getPage(0)->printInfoSector(0);
    manager.getPage(0)->printSizeSector(0);

    manager.getPage(0)->printSize();
    
    return 0;
}