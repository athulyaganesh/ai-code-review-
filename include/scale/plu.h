// PLU (price look-up) table for weighed deli items.
// Legacy-style header kept on purpose: this mirrors an older codebase.
#ifndef SCALE_PLU_H
#define SCALE_PLU_H

#define PLU_DESC_LEN 24

struct PluRecord {
    int  number;                    // e.g. 2001
    char description[PLU_DESC_LEN]; // printed on the label
    long pricePerLbCents;           // price per pound, in cents
};

// Returns the record for a PLU number, or NULL if it does not exist.
const PluRecord* findPlu(int pluNumber);

int pluCount();

#endif
