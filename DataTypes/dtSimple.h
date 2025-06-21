#ifndef DTSIMPLE_H
#define DTSIMPLE_H

#include "dtProducto.h"

#include <iostream>
#include <string>

using namespace std;

class dtSimple:public dtProducto{
    public:
        dtSimple(int,string,float);
        ~dtSimple();
};

#endif //DTSIMPLE_H