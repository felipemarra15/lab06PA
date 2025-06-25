#include "dtSimple.h"

// Constructor
dtSimple::dtSimple(int codigo, string descripcion, float precio) : dtProducto(codigo, descripcion, precio) {
    
}

// Destructor
dtSimple::~dtSimple() {
    // Destructor vacío, no hay recursos que liberar
    // Si hubiera recursos dinámicos, se liberarían aquí
}