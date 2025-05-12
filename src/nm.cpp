#include "nm.h"

#include <stdio.h>
#include "eorzea-time.h"

NM::NM(const char weather_min, const char weather_max, const char* name)
: weather(weather_min, weather_max), name(name)
{}

void NM::stat() const {
    printf("%ld %ld %ld %ld %s\n",
        Time::SECONDS_PER_HOUR *  next.start,
        Time::SECONDS_PER_HOUR * (next.start - prev.end),
        Time::SECONDS_PER_HOUR * (next.start - prev.start),
        Time::SECONDS_PER_HOUR * (next.end   - next.start),
        name
    );
}
