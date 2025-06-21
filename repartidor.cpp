#include "repartidor.h"

#include <iostream>

using namespace std;

//Constructor
Repartidor::Repartidor(int numero, string nombre, string transporte) : Empleado(numero, nombre){
    this -> transporte = transporte;
}

//Destructor
Repartidor::~Repartidor(){
    cout << "Repartidor eliminado" << endl;
}

//Getters
string Repartidor::getTransporte(){
    return this -> transporte;
}

//Setters
void Repartidor::setTransporte(string transporte){
    this -> transporte = transporte;
}

