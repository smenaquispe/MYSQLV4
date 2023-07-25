#include"Page.h"

void Page::printRecord(int idRecord) {

    vector<string> temp = data[idRecord];

    cout<<idRecord<<" ";
    for(string s : temp) {
        cout<<s<<" ";
    }
    
    cout<<endl;
}