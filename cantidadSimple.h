#ifndef CANTIDAD_SIMPLE_H
#define CANTIDAD_SIMPLE_H

#include <iostream>

#include "producto.h"
#include "ICollection/interfaces/ICollectible.h"

class CantidadSimple : public ICollectible {
    private:
        Producto* producto;
        int cantidad;
    public:
        CantidadSimple(Producto* producto, int cantidad);
        ~CantidadSimple();
        Producto* getProducto();
        int getCantidad();
};
#endif