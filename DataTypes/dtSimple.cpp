#include "dtSimple.h"

// Constructor
dtSimple::dtSimple(int codigo, string descripcion, float precio) : dtProducto(codigo, descripcion, precio) {
    
}

// Destructor
dtSimple::~dtSimple() {
    cout << "Destructor de dtSimple" << endl;
}