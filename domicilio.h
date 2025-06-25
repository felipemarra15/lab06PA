#ifndef DOMICILIO_H
#define DOMICILIO_H

#include <iostream>
#include <string>

#include "DataTypes/dtDomicilio.h"
#include "DataTypes/dtVentaProducto.h"
#include "DataTypes/dtProducto.h"

#include "ICollection/interfaces/ICollection.h"


#include "venta.h"

using namespace std;

class Domicilio: public Venta {
    private:
        bool retira;
        Repartidor* repartidor;
        Cliente* cliente;
    public:
        Domicilio(int idVenta,int descuento, bool retira, ICollection* ventaProducto, Factura* factura, Cliente* cliente, Repartidor* repartidor);
        Domicilio(int idVenta,int descuento, bool retira, ICollection* ventaProducto, Factura* factura, Cliente* cliente);
        ~Domicilio();
        bool getRetira();
        Repartidor* getRepartidor();
        Cliente* getCliente();
        void setRetira(bool retira);
        void setRepartidor(Repartidor* repartidor);
        void setCliente(Cliente* cliente);
        dtVenta* mostrarFactura();    
        float calcularTotal();
};

#endif //DOMICILIO_H