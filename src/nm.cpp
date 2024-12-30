#include <stdio.h>

#include "nm.h"

const unsigned char SECONDS_PER_HOUR = 175; // *per in-game hour

void NM::stat() {
    printf("%ld %ld %ld %ld %s\n",
        SECONDS_PER_HOUR *  next.start,
        SECONDS_PER_HOUR * (next.start - prev.end),
        SECONDS_PER_HOUR * (next.start - prev.start),
        SECONDS_PER_HOUR * (next.end   - next.start),
        name
    );
}
