#pragma once

struct Weather {
    const static char DURATION = 8;
    const char min, max;

    Weather(const char& min, const char& max) : min(min), max(max) {}

    bool is_active(const char& seed) const;

    static long chunk(const long& eorzea_hours);

    static char seed(const long& eorzea_hours);
};
