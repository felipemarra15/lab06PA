#include "fecha.h"

// CONSTRUCTOR:
fecha::fecha (){
    this -> dia = this -> mes = this -> anio = 0;
}

fecha::fecha (int d, int m, int a){
    if ( d < 1 || d > 31 || m < 1 || m > 12 || a < 1900){
        throw invalid_argument("Fecha no valida");
    }else{
        this -> dia = d;
        this -> mes = m;
        this -> anio = a;
    }
};

// DESTRUCTOR:
fecha::~fecha(){
    cout << "destruct de fecha" << endl;
}

// GETTERS:
int fecha::getDia(){
    return this -> dia;
}

int fecha::getMes(){
    return this -> mes;
}

int fecha::getAnio(){
    return this -> anio;
}