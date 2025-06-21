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
    float iva;
public:
    Factura(fecha *f, hora *h, float iva);
    ~Factura();
    fecha* getFecha();
    hora* getHora();
    float getIva();
    void setFecha(fecha* f);
    void setHora(hora* h);
    void setIva(float iva);
};
#endif // FACTURA_H