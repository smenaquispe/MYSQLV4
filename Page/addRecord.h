#include"Page.h"

int Page::addRecord() {

    int numeroSector = -1;
    for(auto it = freeSpace.begin(); it != freeSpace.end(); ++it) {
        // significa que tiene espacio y podemos agregar alli...
        if(it->second < maximumSector) {
            numeroSector = it->first;
            break;
        }
    }

    if(numeroSector == -1) {
        return 0;
    }

    cout<<"Agregado en el sector: "<<numeroSector<<endl;

    regex stringRegex(R"(\((.*?)\))");
    ifstream input("./docs/input");
    string line;

    int idRecord;
    string t;

    bool isId = true;
    while (getline(input, line))
    {
        smatch matches;
        string::const_iterator searchStart(line.cbegin());
        while (regex_search(searchStart, line.cend(), matches, stringRegex)) {
            if(isId) {
                idRecord = stoi(matches[1].str());
                
                data[idRecord] = {};

                isId = false;
            } else {
                t = matches[1].str();
                data[idRecord].push_back(t);
            }
            searchStart = matches.suffix().first;
        }
    }
    
    sectores[numeroSector].push_back(idRecord);
    cambio++;

    return 1;
}