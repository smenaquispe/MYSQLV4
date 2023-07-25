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

    // solo si se desea leer un csv
    
    /*
    File f("./titanic.csv");
    f.extractSchema("./docs/schema");
    f.toFile();
    f.printFile();
    */
    

    //Disk d(&f, 5, 7, 4, 5);
    
    Disk d(5, 7, 4, 5);
    //d.loadFile();
    d.run();

    BufferManager manager(&d, 4, 10);

    // este es el el bloque 7
    manager.uploadPage(5);

    // como es el primero se guarda en la pos 0

    manager.getPage(0)->deleteRecord(278);
    manager.getPage(0)->addRecord();
    manager.getPage(0)->printSector(55);
    //manager.printPage(0);

    //manager.printRecord(2);

    return 0;
    
}
