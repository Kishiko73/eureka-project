#include "weather.h"

bool Weather::is_active(const char& seed) const {
    return min <= seed && seed < max;
}

long Weather::chunk(const long& eorzea_hours) {
    return eorzea_hours & ~7L;
}

char Weather::seed(const long& eorzea_hours) {
    long eorzea_days = eorzea_hours / 24,
         time_chunk = (chunk(eorzea_hours) + DURATION) % 24;

    unsigned int seed = eorzea_days * 100 + time_chunk;
    seed ^= seed << 11;
    seed ^= seed >> 8;

    return (char)(seed % 100);
}
