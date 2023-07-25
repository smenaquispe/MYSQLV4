#include"Page.h"

void Page::printRecord(int idRecord) {
    for(auto it = data.begin(); it != data.end(); ++it) {
    
        cout<<it->first<<" ";
        for(int i = 0; i < it->second.size(); i++) 
            cout<<it->second[i]<<" ";
        cout<<endl;
    }
}