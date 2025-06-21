#ifndef DTPRODUCTO_H
#define DTPRODUCTO_H

#include <iostream>
#include <string>

#include "../ICollection/interfaces/ICollectible.h"

using namespace std;

class dtProducto : public ICollectible {
    private:
        int codigo;
        string nombre;
        float precio;
    public:
        dtProducto(int,string,float);
        ~dtProducto();
        int getCodigo();
        string getNombre();
        float getPrecio();
};
#endif //DTPRODUCTO_H
