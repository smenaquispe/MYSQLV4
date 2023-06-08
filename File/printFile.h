#ifndef PRINT_FILE
#define PRINT_FILE

#include"File.h"


void File::printFile() {
    for(int i = 1; i <= this->numberRegisters; i++)
        printFile(i);
}

void File::printFile(int min, int max) {
    for(int i = min; i < max; i++) {
        printFile(i);
    }
}

void File::printFile(int numeroRegistro) {
    ifstream file("./docs/file");

    numeroRegistro--;

    if(file.is_open()) {
        file.seekg((numeroRegistro * this->totalRegisterBytes) + 1);
        file.read(buffer, totalRegisterBytes);

        int prevSize = 0;
        for(int i = 0; i < numberColumns; i++) {
            
            int columnLen = columnBytes[i];
            if(columnLen > 1) columnLen--; // si es uno, no se convertira en 0
            if(columnLen == 1) prevSize--; // si es uno, es necesario retroceder para que imprima como debe de ser

            // cuente desde que punto no hay espacios en blanco
            int startIndex = prevSize;
            while (buffer[startIndex] == ' ') {
                startIndex++;
            }

            // mandamos a imprimir
            cout.write(buffer + startIndex, (columnLen + prevSize)  - startIndex);
            cout<<" ";

            prevSize += columnLen + 1;
        }

        cout<<endl;

        file.close();
    } else {
        cout<<"Problemas abriendo el file"<<endl;
    }
}



#endif