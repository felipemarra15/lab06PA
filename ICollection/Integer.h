#include "interfaces/ICollectible.h"
#include "interfaces/OrderedKey.h"


#ifndef _INTEGER_H
#define	_INTEGER_H

// datatype para representar un entero
class Integer: public ICollectible, public OrderedKey
{
private:
    const int val;
public:
    Integer(int i);
    int getValue() const;
    ComparisonRes compare(OrderedKey *k) const;
};


#endif	/* _INTEGER_H */

