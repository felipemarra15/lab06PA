#ifndef LOCAL_H
#define LOCAL_H

#include <iostream>
#include <string>

// Incluyo la clase base para que el compilador la conozca
#include "venta.h"
#include "factura.h"
#include "mesa.h"
//#include "mozo.h"
#include "ICollection/interfaces/IDictionary.h"
class Mozo; // Declaración anticipada de la clase Mozo

class Local : public Venta {
    private:
        IDictionary* mesa;
        Mozo* mozo;
    public:
        Local(int idVenta, int descuento, ICollection * ventaProducto, Factura* factura, IDictionary* mesa, Mozo* mozo);
        ~Local();
        IDictionary* getMesa();
        Mozo* getMozo();
        void setMozo(Mozo* mozo);
        void setMesa(IDictionary* mesa);
        dtVenta* mostrarFactura();

};
#endif //LOCAL_H