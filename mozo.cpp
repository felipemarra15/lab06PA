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
    cout << "Mozo eliminado!" << endl;
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
