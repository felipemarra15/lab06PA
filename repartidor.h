#ifndef REPARTIDOR_H
#define REPARTIDOR_H

#include <iostream>
#include <string>

#include "empleado.h"

class Repartidor : public Empleado{
    private:
        string transporte;
    public:
        Repartidor(int numero, string nombre, string transporte);
        ~Repartidor();
        string getTransporte();
        void setTransporte(string transporte);
};

#endif //REPARTIDOR_H