// Price calculation for weighed items. All money is integer cents,
// all weights are integer thousandths of a pound (milli-lb) to avoid floating point.
#ifndef SCALE_PRICING_H
#define SCALE_PRICING_H

// Net weight = gross - tare. Returns -1 if the inputs are invalid
// (gross <= 0, tare < 0, or tare >= gross).
long netWeightMilliLb(long grossMilliLb, long tareMilliLb);

// Total price in cents, rounded half-up to the cent.
// Returns -1 for an unknown PLU or invalid weights.
long itemPriceCents(int pluNumber, long grossMilliLb, long tareMilliLb);

#endif
