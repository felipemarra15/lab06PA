#ifndef DTVENTAPRODUCTO_H
#define DTVENTAPRODUCTO_H

#include <iostream>
#include <string>

#include "dtVenta.h"
#include "dtProducto.h"
#include "../ICollection/interfaces/ICollectible.h"
#include "../ICollection/interfaces/ICollection.h"

using namespace std;

class dtVentaProducto : public ICollectible {
    private:
      int cantidad;
      dtProducto *producto;
    public:
        dtVentaProducto(dtProducto *producto, int cantidad);
        ~dtVentaProducto();
        int getCantidad();
        dtProducto* getProducto();
};
#endif //DTVENTAPRODUCTO_H
