#pragma once
#include "weather.h"

//const unsigned char SECONDS_PER_HOUR = 175; // *per in-game hour
extern const unsigned char SECONDS_PER_HOUR;

struct Window {
    // ET hours epoch
    long start, end;
};

struct NM {
    Window prev, next;
    const Weather weather;
    const char* name;

    NM(const char& weather_min, const char& weather_max, const char* name) :
            weather(weather_min, weather_max), name(name) {}

    void stat();
};
