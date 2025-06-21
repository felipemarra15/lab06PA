#ifndef DTLOCAL_H
#define DTLOCAL_H

#include "dtVenta.h"
//#include "../Mozo.h"
#include "../mesa.h"

#include <iostream>
#include <string>

using namespace std;

class dtLocal : public dtVenta {
    private:
        IDictionary* mesa;
        float total; 
    public:
        dtLocal(int idVenta, int descuento, ICollection* ventaProducto, Factura * factura, IDictionary* mesa);
        ~dtLocal();
        IDictionary* getMesa();
        float getTotal();
};

#endif //DTLOCAL_H