#include "eorzea-time.h"

const unsigned char Time::SECONDS_PER_ET_HOUR = 175;

long Time::chunk(const long eorzea_hours) {
    return eorzea_hours & ~7L;
}

