#ifndef FILE_H
#define FILE_H

#include<cstring>
#include<fstream>
#include<iostream>
#include<cstdlib> 
#include<iomanip>
#include<regex>

using namespace std;

class File
{
public:
    File(string csv) {

        this->csv = csv;

        // buffer necessary for read the file
        this->buffer = new char[lenBuffer];
        numberColumns = 0;
        numberRegisters = 0;
        totalRegisterBytes = 0;
    }

    ~File() {
        delete buffer;
    }

    string csv; // get the file or csv

    // properties
    int numberColumns; // number of columns
    int totalRegisterBytes; // what is the total length of a register
    int numberRegisters; // number of registers in the file

    int lenBuffer = 1024;
    char *buffer;

    // methods
    void toFile();
    void extractSchema(string schemaFile);

    // print one
    void printFile(int);
    // print all
    void printFile();
    // print range
    void printFile(int, int);
};

#include"toFile.h"
#include"extractSchema.h"
#include"printFile.h"

#endif