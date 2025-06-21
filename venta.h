#ifndef VENTA_H
#define VENTA_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>

#include "DataTypes/dtVenta.h"
//#include "DataTypes/dtLocal.h"
#include "DataTypes/dtProducto.h"
#include "ICollection/interfaces/ICollection.h"
#include "ICollection/Integer.h"
#include "factura.h"
#include "ventaProducto.h"
//#include "local.h"

using namespace std;

class Venta : public ICollectible {
    private:
        int idVenta;
        int descuento;
        ICollection* ventaProductos;
        Factura* factura;
    public:
        Venta(int idVenta, int descuento, ICollection* ventaProductos, Factura* factura);
        ~Venta();
        int getIdVenta();
        int getDescuento();
        ICollection* getVentaProductos();
        Factura* getFactura();
        void setIdVenta(int idVen);
        void setDescuento(int desc);
        void setVentaProductos(ICollection* ventaProds);
        void setFactura(Factura* factura);
        virtual dtVenta* mostrarFactura() = 0;
        void aumentarCantProducto(int idProducto,int cantidad);
        bool verificarVentasProducto(string verifiqueishon);
        bool esMesa(int idMesa);
        void setDescuento(float porcentaje);
        void eliminarProducto(string producto,int cantidad);
        bool agregarProducto(ventaProducto* vp);

};

#endif