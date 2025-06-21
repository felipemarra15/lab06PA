#include "empleado.h"

#include <iostream>

//Constructor
Empleado::Empleado(int numero, string nombre){
    this -> numero = numero;
    this -> nombre = nombre;
}

//Destructor
Empleado::~Empleado(){
    cout << "Empleado eliminado!"<< endl;
}

//Getters
int Empleado::getNumero(){
    return this -> numero;
}

string Empleado::getNombre(){
    return this -> nombre;
}
