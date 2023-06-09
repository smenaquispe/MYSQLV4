#include"BufferManager.h"

void BufferManager::uploadAllPages() {
    
   // contadores que me ayudaran a setear la metadata
    int contPlatos = 1;
    int contSuperficies = 1;
    int contPistas = 1;
    int contSectores = 1;
    int contBloques = 1; 

    int count = 0;
    int a, b;
    for(int i = 0; i <= disk->numTotalSectores; i++) {
        if(count == 0) {
            a = i;
        }
        
        count++;

        b = i;

        contBloques++;
        contSectores++;

        if(contBloques > NUMBER_SECTORS_PER_CLUSTER) {
            this->uploadPage(a, b, contPlatos, contSuperficies, contPistas);
            count = 0;
            contBloques = 1;
        }

        if(contSectores > disk->numSectores) {
            contSectores = 1;
            contPistas++;
            contBloques = 1; // los bloques solo se encuentran contiguos en una pista

        }

        if(contPistas > disk->numPistas) {
            contPistas = 1;
            contSuperficies++;            
        } 
        
        if(contSuperficies > 2) {
            contSuperficies = 1;
            contPlatos++;
        } 

        if(contPlatos > disk->numPlatos) {
            cout<<"El disco llegó a su maxima capacidad"<<endl;
            break;
        }
    }

}