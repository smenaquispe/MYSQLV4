#include"Page.h"

int Page::printInfoSector(int numberSector) {
    
    if(!(l1 <= numberSector && l2 >= numberSector)) {
        return 0;
    }
    cout<<"Sector nro.: "<<numberSector<<endl;
    cout<<"Se encuentra en el plato nro.: "<<numPlato<<endl;
    cout<<"Se encuentra en la superficie: "<<numSuperficie<<endl;
    cout<<"Se encuentra en la pista nro.: "<<numPista<<endl;

    vector<int> temp = sectores[numberSector];

    cout<<"Registros que almacena el sector: "<<endl;
    for(int i = 0; i < temp.size(); i++) {
        cout<<temp[i]<<" ";
    }
    cout<<endl;

    return 1;
}