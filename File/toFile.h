#ifndef TO_FILE
#define TO_FILE

#include"File.h"
#include"../Utils/myStrtok.h"

void File::toFile() {

    // cree el file a partir del csv y los espacios que alamacena cada uno
    ifstream csvFile(this->csv);
    ofstream file("./docs/file");
    ifstream schema("./Disk/data/meta/schema");

    int currentColumn;
    bool isHeader = true;
    if(csvFile.is_open()) {
        int pos = 0;
        while(csvFile.getline(buffer + pos, lenBuffer)) {
            
            if(!isHeader) {
                int column = 0;
                char * token = myStrtok(buffer + pos, ",");
                while (token != nullptr)
                {
                    schema >> currentColumn;
                    
                    if(strlen(token) != 0) 
                        file<<setw(currentColumn)<<token;
                    else 
                        file<<setw(currentColumn)<<"-";
                                        
                    column++;
                    token = myStrtok(nullptr, ",");
                }

                this->numberRegisters++;
                schema.clear();
                schema.seekg(0);
            }
            
            
            
            if(isHeader) isHeader = false;
            if(pos >= sizeof(buffer)) {
                pos = 0;
            }
        }
    }

}

#endif