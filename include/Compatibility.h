#ifndef COMPATIBILITY_H
#define COMPATIBILITY_H

#ifdef UNIT_TESTING

#ifndef min
#define min(a, b) ((a) < (b) ? (a) : (b))
#endif
#ifndef max
#define max(a, b) ((a) > (b) ? (a) : (b))
#endif

#endif

#endif // COMPATIBILITY_H
