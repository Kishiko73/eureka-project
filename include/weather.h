#pragma once

struct Weather {
    // Duration of a single weather window in Eorzean Hours
    const static char DURATION;
    // min and max seed values of the given weather
    const char min, max;

    Weather(const char min, const char max);

    // if the seed falls under the weather scope
    bool is_active(const char seed) const;

    // generate a weather seed from the epoch time in eorzean hours
    static char seed(const long eorzea_hours);
};
