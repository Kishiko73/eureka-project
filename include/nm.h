#pragma once
#include "weather.h"

struct Window {
    /*
     * start and end time of a given NM window
     * represented as epoch time in Eorzean Hours
     */
    long start, end;
};

struct NM {
    Window prev, next;
    const Weather weather;
    const char* name;

    NM(const char weather_min, const char weather_max, const char* name);

    static void stat_wait(long wait);
    static bool stat_down(char const * const symbol, long down);
    void stat() const;
    void watch() const;
};
