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
    manager.uploadAllPages();

    int opc, number;    
    do
    {
        cout<<"-------DISCO-------"<<endl;
        cout<<"1. Imprimir todos los registros"<<endl;
        cout<<"2. Imprimir un registro"<<endl;
        cout<<"3. Calcular la capacidad del disco"<<endl;
        cout<<"4. Imprimir un sector"<<endl;
        cout<<"5. Informacion de un sector"<<endl;
        cout<<"6. Imprimir un bloque"<<endl;
        cout<<"7. Informcacion de un bloque"<<endl;
        cout<<"8. Agregar registro"<<endl;
        cout<<"9. Remover registro"<<endl;
        cout<<"10. Salir"<<endl;       
        cout<<"Digite su opcion: ";
        cin>>opc;


        switch (opc)
        {
        case 1: manager.printAll(); break;
        case 2: {
            cout<<"Nunero de registro: "; 
            cin>>number;
            manager.printRecord(number);
            cout<<endl;
        } break;
        case 3: manager.printInfoDisk(); break;
        case 4: {
            cout<<"Nombre de sector: ";
            cin>>number;
            manager.printSector(number);
        } break;
        case 5: {
            cout<<"Nombre de sector: ";
            cin>>number;
            manager.printInfoSector(number);
        } break;
        case 6: {
            cout<<"Numero de bloque: ";
            cin>>number;
            manager.printPage(number);
        } break;
        case 7: {
            cout<<"Numero de bloque: ";
            cin>>number;
            manager.getPage(number)->printSize();
        } break;
        case 8: {
            manager.addRecord();
        } break;
        case 9: {
            cout<<"Numero de registro: ";
            cin>>number;
            manager.deleteRecord(number);
        } break;
        case 10: break;
        default:
            cout<<"No es una opcion valida"<<endl;
            break;
        }

    } while (opc != 10);


    return 0;
}