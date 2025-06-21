#ifndef FACTORY_H
#define FACTORY_H

#include "ISistema.h"
#include "sistema.h"

class factory {
    public:
        static ISistema* getSistema();
};

#endif // FACTORY_H