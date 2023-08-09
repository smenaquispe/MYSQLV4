#include"Page.h"

int Page::printInfoSector(int numberSector) {
    
    cout<<"Sector numero: "<<numberSector<<endl;
    for(InfoSectores inf : infoSectores) {
        if(inf.numeroSector == numberSector) {
            cout<<"Se encuentra en el plato nro.: "<<inf.numeroPlato<<endl;
            cout<<"Se encuentra en la superficie: "<<inf.numeroSuperficie<<endl;
            cout<<"Se encuentra en la pista nro.: "<<inf.numeroPista<<endl;
        }
    }

    return 0;
}