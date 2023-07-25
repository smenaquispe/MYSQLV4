#include"Page.h"

int Page::printRecord(int idRecord) {

    auto it = data.find(idRecord);
    
    // no se encontró
    if(it == data.end()) {
        return 0;
    }


    vector<string> temp = data[idRecord];

    cout<<idRecord<<" ";
    for(string s : temp) {
        cout<<s<<" ";
    }
    
    cout<<endl;

    return 1;
}