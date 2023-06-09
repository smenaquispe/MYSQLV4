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

    File f;
    f.setCsv("./titanic.csv");
    f.extractSchema();
    f.toFile();
    
    Disk d(&f);
    d.loadFile();

    // alamcena un máximo de 6 paginas
    // los sectores almacenan 5 registros
    BufferManager manager(6, 5);
    
    manager.uploadPage(106,108);
    manager.uploadPage(0, 5);
    manager.uploadPage(175,178);

    manager.getPage(1)->deleteRecord(2);

    manager.printPage(1);

    return 0;
}