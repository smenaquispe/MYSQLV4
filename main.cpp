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
#include <chrono>

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
        d = new Disk(50, 70, 40, 20);
        d->run();
    } else if (res == 'n'){
        cout<<"Escriba el nombre del file: ";
        string name;
        cin>>name;

        File f("./" + name);
        cout<<"Nombre del schema: ";
        cin>>name;
        f.extractSchema("./docs/" + name);
        f.toFile();

        d = new Disk(&f, 50, 70, 40, 20);
        d->loadFile();
    }
        
    BufferManager manager(d, 4, 100);


    int opc, number;    
    do
    {
        cout<<"-------DISCO-------"<<endl;
        cout<<"1. Plato, superficie, pista y sector están los registros del bloque"<<endl;
        cout<<"2. Consultar un registro"<<endl;
        cout<<"3. Plato, superficie, pista y sector está un registro"<<endl;
        cout<<"4. Adicionar registro"<<endl;
        cout<<"5. Eliminar un registro"<<endl;
        cout<<"6. Mostrar Buffer pool"<<endl;
        cout<<"Digite su opcion: ";
        cin>>opc;

        switch (opc)
        {
        case 1: {
            cout<<"Numero de bloque: ";
            cin>>number;
            auto start = std::chrono::high_resolution_clock::now();
            manager.printInfoBloque(number);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            cout<<"Tiempo de ejecucion: "<<duration<<" milisegundos"<<endl;
        } break;
        case 2: {
            cout<<"Nunero de registro: "; 
            cin>>number;
            manager.printRecord(number);
            cout<<endl;
        } break;
        case 3: {
            cout<<"Nunero de registro: "; 
            cin>>number;
            auto start = std::chrono::high_resolution_clock::now();
            manager.printInfoRecord(number);
            cout<<endl;
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            cout<<"Tiempo de ejecucion: "<<duration<<" milisegundos"<<endl;
        } break;
        case 4: {
            auto start = std::chrono::high_resolution_clock::now();
            manager.addRecord();
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            cout<<"Tiempo de ejecucion: "<<duration<<" milisegundos"<<endl;
            cout<<"Desea guardar los cambios? ";
            cin>>res;
            if(res == 's') {
                manager.save();
            }
        } break;
        case 5: {
            cout<<"Numero de registro: ";
            cin>>number;
            auto start = std::chrono::high_resolution_clock::now();
            manager.deleteRecord(number);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            cout<<"Tiempo de ejecucion: "<<duration<<" milisegundos"<<endl;
            cout<<"Desea guardar los cambios? ";
            cin>>res;
            if(res == 's') {
                manager.save();
                manager.disk->tree->remove({number, 0});
            }
        } break;
        case 6: {
            cout<<"Mostrando Buffer pool..."<<endl;
            manager.mostrarBufferPool();
        } break;
        case 100: manager.printAll(); break;
        case 500: {
            cout<<"Nombre de sector: ";
            cin>>number;
            manager.printSector(number);
        } break;
        case 600: {
            cout<<"Nombre de sector: ";
            cin>>number;
            manager.printInfoSector(number);
        } break;
        case 7: {
            cout<<"Numero de bloque: ";
            cin>>number;
            manager.printPage(number);
        } break;
        case 8: {
            } break;
        case 9: {
            manager.addRecord();
            cout<<"Desea guardar los cambios? ";
            cin>>res;
            if(res == 's') {
                manager.save();
            }
        } break;
        case 10: {
            cout<<"Numero de registro: ";
            cin>>number;
            manager.deleteRecord(number);
            cout<<"Desea guardar los cambios? ";
            cin>>res;
            if(res == 's') {
                manager.save();
                manager.disk->tree->remove({number, 0});
            }
        } break;
        case 11: {
            manager.disk->tree->display();
        }
        case 12: 
            // necesario guardar la metadata
            if(res == 'n')
                d->saveFile();
            
            manager.save();
        break;
        default:
            cout<<"No es una opcion valida"<<endl;
            break;
        }

    } while (opc != 12);



    return 0;
    
}
