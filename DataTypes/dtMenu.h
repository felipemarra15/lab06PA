#ifndef DTMENU_H
#define DTMENU_H

#include <iostream>
#include <string>

#include "dtProducto.h"
#include "../ICollection/interfaces/ICollection.h"

using namespace std;

class dtMenu : public dtProducto {
    private:
        int descuento;
        ICollection* cantidadSimple;
    public:
        dtMenu(int codigo, string descripcion, float precio, int descuento, ICollection* productos);
        ~dtMenu();
        int getDescuento();
        ICollection* getCantidadSimple();
};
#endif
