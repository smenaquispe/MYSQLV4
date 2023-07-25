#include"Page.h"

void Page::saveSectors() {
    /*
        para guardar los cambios de los sectores en disco es necesario realizar los siguientes cambios en disco

        1° cambiar la carpeta sector por la nueva info
        2° setear la metadata del sector con su nuevo metodo de lectura
        3° cambiar el directorio
        4° cambiar el info file aumentando o disminuyendo los numeros de records

    */

    for(auto it = sectores.begin(); it != sectores.end(); it++) {
        int numeroSector = it->first;

        // iteramos los records dentro del sector
        vector<int> records = it->second;
        string for_sector; // para els sector
        string meta; // string para la metadata
        for(int i = 0; i < records.size(); i++ ){
            
            // abrimos el schema
            ifstream schema("./Disk/data/meta/schema");
            int column;
            int acumulado = 0;
            int prevAcumulado = 0;
            schema>>column;

            prevAcumulado = acumulado;
            acumulado +=  column;

            // obteniendo el id del record
            int idRecord = records[i];

            // extraemos la infromacion de la data
            vector<string> data_sector = data[idRecord];
            
            for_sector += to_string(idRecord);

            // comenzamos a sumar a la metadata
            meta += to_string(acumulado - to_string(idRecord).size()) + " " + to_string(acumulado) + " , ";

            for(string s : data_sector) {
                for_sector += s;
                schema >> column;

                prevAcumulado = acumulado;
                acumulado += column;
            
                if(prevAcumulado == acumulado - s.size()) {
                    meta += to_string(acumulado) + " , ";
                } else {
                    meta += to_string(acumulado - s.size()) + " " + to_string(acumulado) + " , ";
                }
            }

            schema.close();
            meta += "\n";
        }

        // abrimos el sector normal
        ofstream sector("./Disk/data/sectors/" + to_string(numeroSector));
        sector<<for_sector;
        // abrimos la metadata del sector
        ofstream meta_sector("./Disk/data/meta/sectors/" + to_string(numeroSector));
        meta_sector<<meta;
    }

    return;
    
    
        // abrir el archivo de metadta del directorio de sectores
    ifstream directory("./Disk/data/meta/directory");

    char buffer[1024];
    if(directory.is_open()) {
        while (directory.getline(buffer, 1024))
        {
            char * token = myStrtok(buffer, " ");

            bool isFirst = true;
            int sector = atoi(token);
            while (token != nullptr)
            {
                if(!isFirst) {
                    freeSpace[sector]++;
                    if(!(l1 <= sector && sector <= l2)) {
                        if(atoi(token))
                            sectores[sector].push_back(atoi(token));
                    }
                }

                else {
                    freeSpace[sector] = -1;
                    isFirst = false;

                    auto it = sectores.find(sector);
                    if(it == sectores.end()) { // significa que no existe
                        sectores[sector] = {};
                    }
                    
                }

                token = myStrtok(nullptr, " ");
            }
                    
        }

        directory.close();
    } else {
        cout<<"Problem open directory"<<endl;
        return;
    }


    ofstream out_directory("./Disk/data/meta/directory");
    for(auto it = sectores.begin(); it != sectores.end(); it++) {
        out_directory<<it->first<<" ";
        for(int p : it->second){
            out_directory<<p<<" ";
        }
        out_directory<<endl;
    }


    string total;
    int num;
    ifstream info_file("./Disk/data/meta/info_file");

    for(int i = 0; i < 3; i++) {
        info_file >> num;

        if(i == 2) {
            num += cambio;
        } 
    
        total += to_string(num);
        total += "\n";
    }

    info_file.close();

    ofstream out_info_file("./Disk/data/meta/info_file");
    out_info_file<<total;

}