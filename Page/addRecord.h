#include"Page.h"

void Page::addRecord() {

    int numeroSector;
    for(auto it = freeSpace.begin(); it != freeSpace.end(); ++it) {
        // significa que tiene espacio y podemos agregar alli...
        if(it->second < maximumSector) {
            numeroSector = it->first;
            break;
        }
    }

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
}