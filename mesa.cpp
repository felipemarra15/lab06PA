#include "mesa.h"

#include<iostream>

using namespace std;

// constructor:

Mesa::Mesa(int idMesa){
    this->idMesa = idMesa;
    this->estado = Finalizada; // Por defecto, la mesa está activa al ser creada
    this->local = NULL; // Inicialmente no está asignada a ningún local
}

// destructor

Mesa::~Mesa(){
    // Si la mesa está asignada a un local, se desvincula
    if (this->local != NULL) {
        this->local->getMesa()->remove(new Integer(this->idMesa)); // Remover la mesa del local
        this->local = NULL; // Desvincular la mesa del local
        delete this->local; // Liberar memoria del local
    }
}

// getters

int Mesa::getidMesa(){
    return this->idMesa;
}

EstadoMesa Mesa::getEstado() {
    return this->estado;
}

// setters

void Mesa::setidMesa(int idMes){
    this->idMesa = idMes;
}

void Mesa::setEstado(EstadoMesa estado){
    this->estado = estado;
}

// funciones
Local* Mesa::getLocal() {
    return this->local;
}

void Mesa::setLocal(Local* local) {
    this->local = local;
}

