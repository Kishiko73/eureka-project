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
