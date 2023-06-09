#include"BufferManager.h"

void BufferManager::printAll() {
    for(int i = 1; i <= disk->file->numberRegisters; i++) {
        printRecord(i);
        cout<<endl;
    }
}