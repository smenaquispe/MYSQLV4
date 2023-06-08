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
using namespace std;

int main() {

    File f;
    f.setCsv("./titanic.csv");
    f.extractSchema();
    f.toFile();
    
    Disk d(&f);
    d.loadFile();

    Page p(3,5);
    p.printSector();
    
    return 0;
}