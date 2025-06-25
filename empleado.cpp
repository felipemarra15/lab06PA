#include "empleado.h"

#include <iostream>

//Constructor
Empleado::Empleado(int numero, string nombre){
    this -> numero = numero;
    this -> nombre = nombre;
}

//Destructor
Empleado::~Empleado(){
    // Destructor vacío, no hay recursos que liberar
    // Si hubiera recursos dinámicos, se liberarían aquí
}

//Getters
int Empleado::getNumero(){
    return this -> numero;
}

string Empleado::getNombre(){
    return this -> nombre;
}
