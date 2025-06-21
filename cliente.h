#ifndef CLIENTE_H
#define CLIENTE_H

#include <iostream>
#include <string>

#include "DataTypes/direccion.h"
#include "ICollection/interfaces/ICollectible.h"

using namespace std;

class Cliente : public ICollectible {
private:
    string ci;
    string nombre;
    string telefono;
    direccion *dir;

public:
    Cliente(string ci, string nombre, string telefono, direccion* dir);
    ~Cliente();
    string getCi();
    string getNombre();
    string getTelefono();
    direccion* getDireccion();
    void setCi(string& ci);
    void setNombre(string& nombre);
    void setTelefono(string& telefono);
    void setDireccion(direccion* dir);
};

#endif // CLIENTE_H
