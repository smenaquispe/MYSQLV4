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

    /*
        LA OPCION DE USAR LO QUE YA HAY EN DISCO
        O NUEVA LECTURA
    */

    char res;
    cout<<"Desea usar lo que esta guardado en disco? (s / n): ";
    cin>>res;

    Disk * d;
    if(res == 's') {
        d = new Disk(5, 7, 4, 5);
        d->run();
    } else if (res == 'n'){
        cout<<"Escriba el nombre del file: ";
        string name;
        cin>>name;

        File f(name);
        f.extractSchema("./docs/schema");
        f.toFile();

        d = new Disk(&f, 5, 7, 4, 5);
        d->loadFile();
    }
        
    BufferManager manager(d, 4, 10);


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
        case 10: 
            //d.saveFile();
        break;
        default:
            cout<<"No es una opcion valida"<<endl;
            break;
        }

    } while (opc != 10);



    return 0;
    
}
