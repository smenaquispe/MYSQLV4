#include"BufferManager.h"

void BufferManager::save() {
    for(int in = 0; in < lenPages; in ++) {
        // hay cambios por realizarse
        if(pages[cualMeQuede].dirtyBit) {
            char res;
            cout<<"Desea guardar los cambios realizados en la pagina: "<<tagPages[cualMeQuede]<<" ? (s / n)"<<endl;
            cin>>res;
            if(res == 's') {
                pages[cualMeQuede].saveSectors(this->disk);
                pages[cualMeQuede].dirtyBit = 0;
            }
        }
        
        //cout<<"Cual me quede ps "<<cualMeQuede<<endl;
        cualMeQuede++;

        if(cualMeQuede == lenPages) {
            cualMeQuede = 0;
        }
    }

}