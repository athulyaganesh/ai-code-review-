#include "scale/plu.h"

#include <stddef.h>

static const PluRecord g_pluTable[] = {
    {4011, "BANANAS", 59},
    {2001, "SMOKED TURKEY", 999},
    {2002, "SWISS CHEESE", 849},
    {2003, "OVEN ROASTED CHICKEN", 749},
};

static const int g_pluCount = sizeof(g_pluTable) / sizeof(g_pluTable[0]);

const PluRecord* findPlu(int pluNumber)
{
    for (int i = 0; i < g_pluCount; i++) {
        if (g_pluTable[i].number == pluNumber) {
            return &g_pluTable[i];
        }
    }
    return NULL;
}

int pluCount()
{
    return g_pluCount;
}
