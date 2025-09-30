/*  Eureka Project - Display upcoming Eureka NMs for FFXIV
 *  Copyright (C) 2025  Kishiko73
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "nm.h"

#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "eorzea-time.h"


struct Colours {
    static const int down_good = 0x00FF00;
    static const int down_medi = 0xFFFF00;
    static const int down_poor = 0xFFAA00;
    static const int wait_good = 0xFFFF00;
    static const int wait_medi = 0xFFAA00;
    static const int wait_poor = 0xFF3300;
};

NM::NM(const char weather_min, const char weather_max, const char* name)
: weather(weather_min, weather_max), name(name)
{}

void NM::stat_wait(long wait) {
    int colour = 0xFFFFFF;
    if (wait <= 60)
        colour = Colours::wait_poor;
    else if (wait <= 300)
        colour = Colours::wait_medi;
    else if (wait <= 1800)
        colour = Colours::wait_good;
    printf("<b><span foreground=\"#%06x\">", colour);

    if (wait > 60)
        printf("%ldm", wait / 60);
    else
        printf("%lds", wait);
    printf("</span></b> ");
}

bool NM::stat_down(char const * const symbol, long down) {
    down = Time::SECONDS_PER_ET_HOUR * down / 60;
    int colour = Colours::down_poor;
    if (down >= 120)
        colour = Colours::down_good;
    else if (down >= 116)
        colour = Colours::down_medi;

    printf("%s<span foreground=\"#%06x\">%ld</span>", symbol, colour, down);

    return colour != Colours::down_good;
}

/**
 * Display the status of the current NM using pango markup
 *
 * NM name                 (string)
 * time until window start (minutes / seconds)
 * next.start - prev.end   (minutes)
 * next.start - prev.start (minutes)
 * next.end   - prev.start (minutes)
 */
void NM::stat() const {
    printf("%s ", name);

    stat_wait(Time::SECONDS_PER_ET_HOUR * next.start - time(NULL));

    if (stat_down("▼", next.start - prev.end  )) // worst case downtime
    if (stat_down("◆", next.start - prev.start)) // expected   downtime
        stat_down("▲", next.end   - prev.start); // best  case downtime

    printf("\n");
    fflush(stdout); // for i3blocks persistent interval to update correctly
}

void NM::watch() const {
    long start = Time::SECONDS_PER_ET_HOUR * next.start;

    // align remaining time to MM:59
    if (start - time(NULL) > 60) {
        stat();
        sleep((start - time(NULL)) % 60 + 1);
    }

    // restat every minute, or every second when 60s remain
    while (start - time(NULL) > 0) {
        stat();
        if (start - time(NULL) > 60)
            sleep(60);
        else
            sleep(1);
    }
}
