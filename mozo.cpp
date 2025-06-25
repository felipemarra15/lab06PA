#include "mozo.h"

#include <iostream>

//Constructor
Mozo::Mozo(int numero, string nombre, int idMozo) : Empleado(numero, nombre){
    this -> idMozo = idMozo;
    this -> mesa = new List();
    this -> cantMesas = 0;
}

//Destructor
Mozo::~Mozo(){
    IIterator* it = mesa->getIterator();
    while (it->hasCurrent()) {
        ICollectible* col = it->getCurrent();
        Mesa* m = dynamic_cast<Mesa*>(col);
        if (m) {
            this->mesa->remove(col); // Liberar memoria de cada mesa
        }
        it->next();
    }

    delete it;
    delete mesa; // Liberar la colección de mesas
}

//Getters
int Mozo::getIdMozo(){
    return this -> idMozo;
}

ICollection* Mozo::getMesa(){
    return this -> mesa;
}

int Mozo::getCantMesas(){
    return this -> cantMesas;
}

//Setters
void Mozo::setIdMozo(int idMozo){
    this -> idMozo = idMozo;
}

void Mozo::setMesa(ICollection* mesa){
    if(this -> cantMesas < 2)
        this -> mesa = mesa;
    else
        cout << "No se pueden agregar más mesas al mozo." << endl;
}

void Mozo::setCantMesas(int cantMesas){
    this -> cantMesas = cantMesas;
}
