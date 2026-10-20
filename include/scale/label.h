// Label formatting and container tare presets.
#ifndef SCALE_LABEL_H
#define SCALE_LABEL_H

#define LABEL_LINE_LEN 32
#define MAX_CAPACITY_MILLI_LB 30000   // 30 lb legal capacity

// Tare for a container code ("CUP8", "TRAY1", ...), converted from grams to milli-lb.
// Returns -1 for an unknown container.
long containerTareMilliLb(const char* containerCode);

// Rejects weights above the scale's legal capacity. Returns 0 if OK, -1 if over capacity.
int checkCapacity(long grossMilliLb);

// Writes "<DESCRIPTION>  $<price>" into out (at least LABEL_LINE_LEN chars).
// Returns 0 on success, -1 for an unknown PLU.
int formatLabelLine(int pluNumber, long priceCents, char* out);

// Unit price for the shelf label, in cents per 100 g.
long pricePer100gCents(long priceCents, long netMilliLb);

// Builds one label line per PLU in a print batch. Caller frees the result.
char** buildLabelBatch(const int* plus, const long* pricesCents, int count);
void freeLabelBatch(char** batch, int count);

#endif
