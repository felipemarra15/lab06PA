#ifndef HORA_H
#define HORA_H

#include <iostream>

using namespace std;

class hora
{
private:
    int ora, minuto;
public:
    hora(int ora, int minuto);
    hora();
    ~hora();
    int getOra();
    int getMinuto();
};
#endif