#include "hora.h"

// CONSTRUCTOR:
hora::hora (){
    this -> ora = this -> minuto = 0;
}

hora::hora (int h, int m){
    if (h > 23 || m > 59){
        throw invalid_argument("Hora no valida");
    }else{
        this -> ora = h;
        this -> minuto = m;
    }
};

// DESTRUCTOR:
hora::~hora(){
    cout << "destruct de hora" << endl;
}

// GETTERS:
int hora::getOra(){
    return this -> ora;
}

int hora::getMinuto(){
    return this -> minuto;
}
