#ifndef DTVENTA_H
#define DTVENTA_H

#include <iostream>
#include <string>

#include "../ICollection/interfaces/ICollection.h"
#include "../ICollection/interfaces/ICollectible.h"
#include "../factura.h"

using namespace std;

class dtVenta : public ICollectible {
    private:
        int idVenta;
        int descuento;
        ICollection* ventaProductos;
        Factura* factura;
    public:
        dtVenta(int idVenta, int descuento, ICollection* ventaProductos, Factura* factura);
        ~dtVenta();
        int getIdVenta();
        int getDescuento();
        Factura* getFactura();
        ICollection* getVentaProductos();
};

#endif