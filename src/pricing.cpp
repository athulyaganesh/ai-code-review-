#include "scale/pricing.h"
#include "scale/plu.h"

#include <stddef.h>

long netWeightMilliLb(long grossMilliLb, long tareMilliLb)
{
    if (grossMilliLb <= 0 || tareMilliLb < 0 || tareMilliLb >= grossMilliLb) {
        return -1;
    }
    return grossMilliLb - tareMilliLb;
}

long itemPriceCents(int pluNumber, long grossMilliLb, long tareMilliLb)
{
    const PluRecord* plu = findPlu(pluNumber);
    if (plu == NULL) {
        return -1;
    }

    long net = netWeightMilliLb(grossMilliLb, tareMilliLb);
    if (net < 0) {
        return -1;
    }

    // cents * milli-lb / 1000, rounded half-up
    return (plu->pricePerLbCents * net + 500) / 1000;
}
