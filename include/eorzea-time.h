#pragma once

namespace Time {
    // number of seconds per in-game hour (175)
    extern const unsigned char SECONDS_PER_HOUR;

    // allign time to weather window intersections
    long chunk(const long eorzea_hours);
};
