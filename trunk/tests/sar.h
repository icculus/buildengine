#ifndef COMPAT_SAR_H
#define COMPAT_SAR_H 1

extern int hbits[64];

#define shift_algebraic_right(value,distance) \
(((value) >> (distance))| \
 (hbits[(distance) + (((value) & 0x80000000) >> 26)]))

#endif /* COMPAT_SAR_H */
