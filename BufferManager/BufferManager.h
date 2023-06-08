#ifndef BUFFER_MANAGER_H
#define BUFFER_MANAGER_H

#include<vector>
#include"../Page/Page.h"

using namespace std;

class BufferManager
{
public:

    vector<Page *> pages;

    BufferManager(int lenPages) {
        pages.resize(lenPages);
    }

    ~BufferManager() {}
};


#endif