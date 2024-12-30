#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <array>

#include "weather.h"
#include "nm.h"

// magically included with nm.h, not sure how I feel about this
// const unsigned char SECONDS_PER_HOUR = 175; // *per in-game hour

std::array NMS{
    NM(46,  64, "Skoll"),
    NM(82, 100, "Cassie"),
    NM(10,  28, "Arthro / Penny"),
    NM(30,  60, "Pazuzu")
};

void get_previous_window(const Weather& weather, Window& window) {
    while (!weather.is_active(Weather::seed(window.end -= Weather::DURATION)));
    window.start = window.end;
    // NOTE:
    // window.end is currently aligned to the start of the weather window
    // it does not get algined to the end until get_end_of_window()

    while (weather.is_active(Weather::seed(window.start -= Weather::DURATION)));
    // offset back inside weather window
    window.start += Weather::DURATION;
}

void get_end_of_window(const Weather& weather, long& window_end) {
    while (weather.is_active(Weather::seed(window_end += Weather::DURATION)));
}

void init(const long& eorzea_hours) {
    for (NM& nm : NMS) {
        nm.next.end = eorzea_hours;
        get_previous_window(nm.weather, nm.next);
        get_end_of_window(nm.weather, nm.next.end);
    }
}

void process_weather_window(const long& eorzea_hours) {
    char seed = Weather::seed(eorzea_hours);
    for (NM& nm : NMS) {
        if (eorzea_hours <= nm.next.end)
            continue; // next already calculated
        if (!(nm.weather.is_active(seed)))
            continue;
        // new window
        nm.prev = nm.next;
        nm.next.start = nm.next.end = eorzea_hours;
        get_end_of_window(nm.weather, nm.next.end);
        nm.stat();
    }
}

/*
 * output upcoming statistics for weather windows
 * with the following format, separated by spaces on a single line
 *
 * window start time:    epoch seconds
 *   end-start downtime: seconds
 * start-start downtime: seconds
 * window duration:      seconds
 * NM name:              string
 *
 * optionally accepts a start time in +%s format
 */
int main(int argc, char *argv[]) {
    long epoch_seconds = argc > 1
            ? atoi(argv[1])
            : time(NULL);
    long ET_chunk = Weather::chunk(epoch_seconds / SECONDS_PER_HOUR);

    init(ET_chunk);
    for (int i = 64; --i >= 0; )
        process_weather_window(ET_chunk += Weather::DURATION);
    return 0;
}
