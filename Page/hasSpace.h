#include"Page.h"

// retorna si el bloque tiene espacio suficiente para almacenar otro registro
bool Page::hasSpace() {
    for (auto it = freeSpace.begin(); it != freeSpace.end(); ++it) {
        if(it->second < maximumSector) {
            return true;
        }
    }

    return false;
}