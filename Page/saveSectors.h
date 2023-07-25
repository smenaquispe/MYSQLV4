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

        // abrimos el sector normal
        ofstream sector("./Disk/data/sectors/" + numeroSector);
        // abrimos la metadata del sector
        ofstream meta_sector("./Disk/data/meta/sectors/" + numeroSector);


        // iteramos los records dentro del sector
        vector<int> records = it->second;
        for(int i = 0; i < records.size(); i++ ){
            
            string meta; // string para la metadata
            // abrimos el schema
            ifstream schema("./Disk/data/meta/schema");
            int column;
            int acumulado = 0;
            schema>>column;

            acumulado +=  column;

            // obteniendo el id del record
            int idRecord = records[i];

            // extraemos la infromacion de la data
            vector<string> data_sector = data[idRecord];
            
            cout<<idRecord<<" ";

            // comenzamos a sumar a la metadata
            meta += to_string(acumulado - to_string(idRecord).size()) + " " + to_string(acumulado) + " , ";

            for(string s : data_sector) {
                cout<<s<<" ";
                schema >> column;
                acumulado += column;
            
                meta += to_string(acumulado - s.size()) + " " + to_string(acumulado) + " , ";
            }

            schema.close();
            cout<<endl;
            meta += "\n";
            cout<<meta;
        }

        cout<<endl;
    }

    
    
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

    for(auto it = sectores.begin(); it != sectores.end(); it++) {
        cout<<it->first<<" ";
        for(int p : it->second){
            cout<<p<<" ";
        }
        cout<<endl;
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

    cout<<total;

}