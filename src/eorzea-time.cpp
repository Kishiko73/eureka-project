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

#include "eorzea-time.h"


const unsigned char Time::SECONDS_PER_ET_HOUR = 175;

long Time::chunk(const long eorzea_hours) {
    return eorzea_hours & ~7L;
}

