#ifndef EMPLEADO_H
#define EMPLEADO_H

#include <iostream>
#include <string>

#include "ICollection/interfaces/ICollectible.h"

using namespace std;

class Empleado : public ICollectible {
    private:
        int numero;
        string nombre;
    public:
        Empleado(int numero, string nombre);
        ~Empleado();
        int getNumero();
        string getNombre();
};

#endif //EMPLEADO_H