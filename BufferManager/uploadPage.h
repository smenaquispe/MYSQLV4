#include"BufferManager.h"


void BufferManager::uploadPage(int l1, int l2, int n, int p, int q) {
    Page * page = new Page(l1, l2, NUMBER_REGISTER_PER_SECTOR, n, p , q);

    // aqui se implementará donde se encuentra (clock)
    pages[countPages++] = *page;
}

void BufferManager::uploadPage(int numeroBloque) {

    // el bloque parte desde este punto
    int l1 = this->NUMBER_SECTORS_PER_CLUSTER * numeroBloque;
    
    int contPlato = 0;
    int contSuperficie = 0;
    int contPista = 0;
    int contSectores = 0;

    for(int i = 0; i <= disk->numTotalSectores; i++) {
        
        if(i == l1) {
            int l2 = l1 + NUMBER_SECTORS_PER_CLUSTER - 1;

            // si es el ultimo bloque, no puede acceder a mas sectores
            if(l2 > disk->numTotalSectores) {
                l2 = disk->numTotalSectores;
            }

            uploadPage(l1, l2, contPlato, contSuperficie, contPista);

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
            return;
        }
    }
    
}