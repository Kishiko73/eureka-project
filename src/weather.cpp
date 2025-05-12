#include "weather.h"

#include "eorzea-time.h"

const char Weather::DURATION = 8;

Weather::Weather(const char min, const char max)
: min(min), max(max)
{}

bool Weather::is_active(const char seed) const {
    return min <= seed && seed < max;
}

char Weather::seed(const long eorzea_hours) {
    long eorzea_days = eorzea_hours / 24,
         time_chunk = (Time::chunk(eorzea_hours) + DURATION) % 24;

    unsigned int seed = eorzea_days * 100 + time_chunk;
    seed ^= seed << 11;
    seed ^= seed >> 8;

    return (char)(seed % 100);
}
