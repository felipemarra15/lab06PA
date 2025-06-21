#include "factory.h"

ISistema* factory::getSistema() {
    return Sistema::getInstance();
}