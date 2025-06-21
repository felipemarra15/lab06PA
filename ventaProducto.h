#ifndef VENTAPRODUCTO_H
#define VENTAPRODUCTO_H

#include <iostream>
#include <string>

#include "ICollection/interfaces/ICollectible.h"
#include "producto.h"


using namespace std;

class ventaProducto : public ICollectible {
    private:
        int cantidad;
        Producto* producto;
    public:
        ventaProducto(int cantidad, Producto* producto);
        ~ventaProducto();
        int getCantidad();
        Producto* getProducto();
        void setCantidad(int cantidad);
        void setProducto(Producto* producto);
        bool esProducto(int codigo);
        bool ubicarProducto(int idProducto);
};
#endif //VENTAPRODUCTO_H