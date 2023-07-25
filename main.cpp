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
    d.loadFile();


    BufferManager manager(&d, 4, 10);
    manager.uploadPage(0);
    
    
    return 0;
    
}
