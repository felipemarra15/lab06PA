#ifndef SIMPLE_H
#define SIMPLE_H

#include "producto.h"
#include "DataTypes/dtSimple.h"

class Simple : public Producto {
public:
    Simple(int codigo, string descripcion, float precio);
    ~Simple();
    dtSimple* getProducto();
};

#endif // SIMPLE_H
