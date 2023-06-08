#ifndef TO_FILE
#define TO_FILE

#include"File.h"
#include"../Utils/myStrtok.h"

void File::toFile() {

    // cree el file a partir del csv y los espacios que alamacena cada uno
    ifstream csvFile(this->csv);
    ofstream file("./docs/file");

    bool isHeader = true;
    if(csvFile.is_open()) {
        int pos = 0;
        while(csvFile.getline(buffer + pos, lenBuffer)) {
            
            if(!isHeader) {
                int column = 0;
                char * token = myStrtok(buffer + pos, ",");
                while (token != nullptr)
                {
                    if(strlen(token) != 0) 
                        file<<setw(this->columnBytes[column])<<token;
                    else 
                        file<<setw(this->columnBytes[column])<<"-";
                    column++;
                    token = myStrtok(nullptr, ",");
                }
                this->numberRegisters++;
            }

            
            if(isHeader) isHeader = false;
            if(pos >= sizeof(buffer)) {
                pos = 0;
            }
        }
    }

}

#endif