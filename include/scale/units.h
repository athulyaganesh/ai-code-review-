/*
 * units.h - weight unit conversions
 *
 * Original: 2009. Patched 2012 (metric), 2015 (oz labels), 2019 (milli-lb).
 * NOTE: some functions below are no longer called. Do not remove without
 * checking the plant firmware build (see ticket SCL-1123).
 */
#ifndef SCALE_UNITS_H
#define SCALE_UNITS_H

#define MILLI_LB_PER_LB   1000
#define OZ_PER_LB         16
#define GRAMS_PER_LB_X1000 453592   /* grams per lb * 1000, integer math */

#define UNIT_LB  0
#define UNIT_KG  1
#define UNIT_OZ  2   /* added 2015 */
#define UNIT_GR  3   /* never shipped */

/* Current API (2019+) */
long gramsToMilliLb(long grams);
long milliLbToGrams(long milliLb);

/* Legacy API (pre-2019), kept for old firmware. */
int  ConvertWeight(int value, int fromUnit, int toUnit);
double LbToKg(double lb);
char* UnitName(int unit);

#endif /* SCALE_UNITS_H */
