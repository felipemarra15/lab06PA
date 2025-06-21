#ifndef FECHA_H
#define FECHA_H

#include <iostream>

using namespace std;

class fecha
{
private:
    int dia, mes, anio;
public:
    fecha(int dia, int mes, int anio);
    fecha();
    ~fecha();
    int getDia();
    int getMes();
    int getAnio();
};
#endif