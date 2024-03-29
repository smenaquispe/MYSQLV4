#include"BufferManager.h"

int BufferManager::uploadPage(int numeroBloque, int l1, int l2, vector<InfoSectores> infoSectores) {
    
    Page * page = new Page(numeroBloque, l1, l2, NUMBER_REGISTER_PER_SECTOR, infoSectores);

    // buscamos que en el frame haya espacio libre
    while(true) {
        
        // si se encuentra vacio
        if(vidaPages[cualMeQuede] == 0) {
            
            if(!pages[cualMeQuede].pinCount == 0) {
                char res;
                cout<<"Desea reemplazar la pagina "<<tagPages[cualMeQuede]<<" del frame: "<< cualMeQuede <<"? (s / n) el pincount es de: "<<pages[cualMeQuede].pinCount<<endl;
                cin>>res;
                if(res == 'n') {
                    cualMeQuede++;
                    cout<<"cual me quede: "<<cualMeQuede<<endl;
                    if(cualMeQuede == lenPages) {
                        cualMeQuede = 0;
                    }
                    continue;
                }
            }

            // hay cambios por realizarse
            if(pages[cualMeQuede].dirtyBit) {
                char res;
                cout<<"Desea guardar los cambios realizados en la pagina: "<<tagPages[cualMeQuede]<<" ? (s / n)"<<endl;
                cin>>res;
                if(res == 's') {
                    pages[cualMeQuede].saveSectors(this->disk);
                }
            }

            pages[cualMeQuede] = *page;
            vidaPages[cualMeQuede] = 2;
            tagPages[cualMeQuede] = numeroBloque;
            seleccionables[cualMeQuede] = true;

            //cout<<numeroBloque<< " subido a pagina: "<<cualMeQuede<<endl;
            return cualMeQuede;           
        }

        if(vidaPages[cualMeQuede] > 0) {
            vidaPages[cualMeQuede]--;
        }

        //cout<<"Cual me quede ps "<<cualMeQuede<<endl;
        cualMeQuede++;

        if(cualMeQuede == lenPages) {
            cualMeQuede = 0;
        }
    }

    return -1;

}

int BufferManager::uploadPage(int numeroBloque) {

    // el bloque parte desde este punto
    int l1 = this->NUMBER_SECTORS_PER_CLUSTER * numeroBloque;
    
    int contPlato = 0;
    int contSuperficie = 0;
    int contPista = 0;
    int contSectores = 0;

    vector<InfoSectores> infoSectores;

    int l2 = l1;
    for(int i = 0; i <= disk->numTotalSectores; i++) {
        
        if(i >= l1) {
            infoSectores.push_back({l2, contPlato, contSuperficie, contPista});
            l2++;
            // si es el ultimo bloque, no puede acceder a mas sectores
            if(l2 > disk->numTotalSectores) {
                l2 = disk->numTotalSectores;
                return uploadPage(numeroBloque, l1, l2, infoSectores);
            }
        }

        if(l2 == l1 + NUMBER_SECTORS_PER_CLUSTER -1) {
            return uploadPage(numeroBloque, l1, l2, infoSectores);
        }

        contSectores++;


        if(contSectores > disk->numSectores) {
            contSectores = 0;
            contPista++;
        }

        if(contPista > disk->numPistas) {
            contPista = 0;
            contSuperficie++;
        }

        if(contSuperficie > 1) {
            contSuperficie = 0;
            contPlato++;
        }

        if(contPlato > disk->numPlatos) {
            cout<<"Valor maximo alcanzado en el disco"<<endl;
            return 0;
        }
    }
    
    return 0;
}