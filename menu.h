#ifndef MENU_H
#define MENU_H

#include <cstdlib>

#include "producto.h"
#include "ICollection/interfaces/IDictionary.h"
#include "ICollection/Integer.h"

class Menu : public Producto{
private:
    int descuento;
    IDictionary* cantidadSimple;
public:
    Menu(int codigo, string descripcion, float precio, int descuento, IDictionary* cantidadSimple);
    ~Menu();
    int getDescuento();
    IDictionary* getCantidadSimple();
    void setDescuento(int descuento);
    void setCantidadSimple(IDictionary* cantidadSimple);
    bool verificarProductoEnMenu(string codigo);
    void agregarProducto(IDictionary* cantidadSimple);
    bool esVacio();
    bool esProducto(string codigo);
};
#endif // MENU_H