#ifndef DTDOMICILIO_H
#define DTDOMICILIO_H

#include <iostream>
#include <string>

#include "dtVenta.h"
#include "../repartidor.h"
#include "../cliente.h"

using namespace std;

class dtDomicilio : public dtVenta {
    private:
        bool retira;
        Repartidor* repartidor;
        Cliente* cliente;
    public:
        dtDomicilio(int idVenta, int descuento, ICollection* ventaProducto, Factura* factura, bool retira, Cliente* cliente, Repartidor* repartidor);
        dtDomicilio(int idVenta, int descuento, ICollection* ventaProducto, Factura* factura, bool retira, Cliente* cliente);
        ~dtDomicilio();
        bool getRetira();  
        Repartidor* getRepartidor(); 
};

#endif