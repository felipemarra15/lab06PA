#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <iostream>
#include <string>
#include <cstdlib>

#include "ICollection/interfaces/IDictionary.h"
#include "DataTypes/dtProducto.h"

using namespace std;

class Producto : public ICollectible {
    private:
        int codigo;
        string nombre;
        float precio;
    public:
        Producto(int codigo, string nombre, float precio);
        ~Producto();
        int getCodigo();
        string getNombre();
        float getPrecio();
        void setCodigo(int codigo);
        void setNombre(string nombre);
        void setPrecio(float precio);
        bool esProducto(string codigo);
        dtProducto* mostrarFactura();

};
#endif //PRODUCTO_H
