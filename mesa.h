#ifndef MESA_H
#define MESA_H

enum EstadoMesa { Activa, Finalizada};

#include <iostream>
#include <string>
#include "ICollection/interfaces/IDictionary.h"
#include "venta.h"
#include "local.h"
#include "mozo.h"

class Local;

class Mesa :public ICollectible {
    private:
        int idMesa;
        EstadoMesa estado;
        Local* local;
    public:
        Mesa(int idMesa);
        ~Mesa();
        int getidMesa();
        Local* getLocal();
        EstadoMesa getEstado();
        void setEstado(EstadoMesa estado);
        void setidMesa(int idMes);
        void setLocal(Local* local);
};
#endif // MESA_H