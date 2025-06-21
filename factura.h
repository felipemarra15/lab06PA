#ifndef FACTURA_H
#define FACTURA_H

#include <iostream>
#include <string>

#include "DataTypes/fecha.h"
#include "DataTypes/hora.h"

class Factura {
private:
    fecha* f;
    hora* h;
    int iva;
public:
    Factura(fecha *f, hora *h, int iva);
    ~Factura();
    fecha* getFecha();
    hora* getHora();
    int getIva();
    void setFecha(fecha* f);
    void setHora(hora* h);
    void setIva(int iva);
};
#endif // FACTURA_H