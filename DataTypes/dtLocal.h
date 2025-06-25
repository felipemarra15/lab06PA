#ifndef DTLOCAL_H
#define DTLOCAL_H

#include "dtVenta.h"
#include "../mozo.h"
#include "../mesa.h"


#include <iostream>
#include <string>

using namespace std;

class dtLocal : public dtVenta {
    private:
        IDictionary* mesa;
        Mozo* mozo; // Asumimos que Mozo es una clase definida en otro lugar
        float total; // Total de la venta
    public:
        dtLocal(int idVenta, int descuento, ICollection* ventaProducto, Factura * factura, IDictionary* mesa, Mozo* mozo);
        dtLocal(int idVenta, int descuento, ICollection* ventaProducto, Factura * factura, IDictionary* mesa);
        ~dtLocal();
        IDictionary* getMesa();
        float getTotal();
};

#endif //DTLOCAL_H