#ifndef MOZO_H
#define MOZO_H

#include <iostream>
#include <string>

#include "empleado.h"
#include "mesa.h"
#include "ICollection/interfaces/ICollection.h"
#include "ICollection/collections/List.h"

using namespace std;

class Mozo : public Empleado {
    private:
        int idMozo;
        ICollection* mesa;
        int cantMesas;
    public:
    Mozo(int numero, string nombre, int idMozo);
    ~Mozo();
    int getIdMozo();
    ICollection* getMesa();
    int getCantMesas();    
    void setIdMozo(int idMozo);
    void setMesa(ICollection* mesa);
    void setCantMesas(int cantMesas);
};

#endif //MOZO_H