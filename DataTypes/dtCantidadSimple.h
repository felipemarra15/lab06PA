#ifndef DTCANTIDAD_SIMPLE_H
#define DTCANTIDAD_SIMPLE_H

#include <iostream>

#include "../producto.h"
#include "../ICollection/interfaces/ICollectible.h"

class dtCantidadSimple : public ICollectible {
    private:
        Producto* producto;
        int cantidad;
    public:
        dtCantidadSimple(Producto* producto, int cantidad);
        ~dtCantidadSimple();
        Producto* getProducto();
        int getCantidad();
};
#endif