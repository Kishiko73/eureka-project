#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "eorzea-time.h"
#include "nm.h"
#include "weather.h"

NM NMS[] = {
    NM(46,  64, "Skoll"),
    NM(82, 100, "Cassie"),
    NM(10,  28, "Arthro / Penny"),
    NM(30,  60, "Pazuzu")
};

void get_end_of_window(const Weather& weather, long& window_end) {
    while (weather.is_active(Weather::seed(window_end += Weather::DURATION)));
}

void get_previous_window(const Weather& weather, Window& window) {
    while (!weather.is_active(Weather::seed(window.end -= Weather::DURATION)));
    window.start = window.end;
    get_end_of_window(weather, window.end);

    while (weather.is_active(Weather::seed(window.start -= Weather::DURATION)));
    // offset back inside weather window
    window.start += Weather::DURATION;
}

void init(long eorzea_hours) {
    // Align to end of weather window
    eorzea_hours += Weather::DURATION;

    for (NM& nm : NMS) {
        nm.prev.end = eorzea_hours;
        get_previous_window(nm.weather, nm.prev);
    }
}

void process_weather_window(const long eorzea_hours) {
    const char seed = Weather::seed(eorzea_hours);
    for (NM& nm : NMS) {
        if (eorzea_hours <= nm.prev.end)
            continue;
        // previous window still active

        if (!nm.weather.is_active(seed))
            continue;
        // new window active

        // calculate window duration
        nm.next.start = nm.next.end = eorzea_hours;
        get_end_of_window(nm.weather, nm.next.end);

        nm.watch();
        nm.prev = nm.next;
    }
}

/**
 * output upcoming statistics for NM weather windows
 * with the format specified by `NM::stat`
 *
 * optionally accepts a start time in +%s format
 */
int main(int argc, char *argv[]) {
    long epoch_seconds = argc > 1
            ? atoi(argv[1])
            : time(NULL);
    long ET_chunk = Time::chunk(epoch_seconds / Time::SECONDS_PER_ET_HOUR);

    init(ET_chunk);
    for (;;)
        process_weather_window(ET_chunk += Weather::DURATION);
    return 0;
}
