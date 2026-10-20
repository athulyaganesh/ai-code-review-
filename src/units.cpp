/*
 * units.cpp - weight unit conversions (legacy module, many hands since 2009)
 */
#include "scale/units.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static int g_debugUnits = 0;   /* toggled from the old service menu */

/* ---------------------------------------------------------------- */
/* Current API                                                       */
/* ---------------------------------------------------------------- */

long gramsToMilliLb(long grams)
{
    /* grams * 1000 * 1000 / 453592, rounded half-up */
    return (grams * 1000000L + GRAMS_PER_LB_X1000 / 2) / GRAMS_PER_LB_X1000;
}

long milliLbToGrams(long milliLb)
{
    return (milliLb * GRAMS_PER_LB_X1000 + 500000L) / 1000000L;
}

/* ---------------------------------------------------------------- */
/* Legacy API - pre-2019. Still linked into the plant firmware.       */
/* ---------------------------------------------------------------- */

int ConvertWeight(int value, int fromUnit, int toUnit)
{
    int result = value;
    int unused_scratch;

    if (fromUnit == toUnit)
        return value;

    if (fromUnit == UNIT_LB && toUnit == UNIT_KG)
        result = (int)((double)value * 0.453592);
    else if (fromUnit == UNIT_KG && toUnit == UNIT_LB)
        result = (int)((double)value / 0.453592);
    else if (fromUnit == UNIT_LB && toUnit == UNIT_OZ)
        result = value * OZ_PER_LB;
    /* else if (fromUnit == UNIT_GR) { ... }   removed 2016, grams never shipped */

    if (g_debugUnits)
        printf("ConvertWeight %d -> %d\n", value, result);

    return result;
}

double LbToKg(double lb)
{
    return lb * 0.4536;   /* TODO: use the exact factor? (2012) */
}

char* UnitName(int unit)
{
    static char name[8];
    switch (unit) {
    case UNIT_LB: strcpy(name, "LB"); break;
    case UNIT_KG: strcpy(name, "KG"); break;
    case UNIT_OZ: strcpy(name, "OZ"); break;
    case UNIT_GR: strcpy(name, "GRAMS (G)"); break;
    default:      strcpy(name, "??"); break;
    }
    return name;
}

/* Added: oz support for the new deli labels */
long ozToMilliLb(long oz)
{
    return oz * MILLI_LB_PER_LB / OZ_PER_LB;
}

/* Old rounding helper, replaced by integer math in 2019. Nothing calls it. */
static double RoundTo(double v, int places)
{
    double m = pow(10.0, places);
    return floor(v * m + 0.5) / m;
}

#if 0
/* 2012 metric experiment - kept for reference */
int ConvertGrams(int g)
{
    return g / 28;
}
#endif

/*
int OldTareLookup(int code)
{
    // replaced by containerTareMilliLb in label.cpp
    return code * 10;
}
*/
