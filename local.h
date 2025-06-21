#ifndef LOCAL_H
#define LOCAL_H

#include <iostream>
#include <string>

// Incluyo la clase base para que el compilador la conozca
#include "venta.h"
#include "factura.h"
#include "mesa.h"
#include "ICollection/interfaces/IDictionary.h"

class Local : public Venta {
    private:
        IDictionary* mesa;
    public:
        Local(int idVenta, int descuento, ICollection * ventaProducto, Factura* factura, IDictionary* mesa); 
        ~Local();
        IDictionary* getMesa();
        void setMesa(IDictionary* mesa);
        dtVenta* mostrarFactura();

};
#endif //LOCAL_H