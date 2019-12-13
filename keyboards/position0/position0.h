/* Copyright 2019 ginjake
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef POSITION0_H
#define POSITION0_H

#include "quantum.h"
#define LAYOUT( \
    k00, k01, k02, k03, k04, k05, k06,\
    k07, k08, k09, k10, k11, k12, k13,\
    k14, k15, k16, k17, k18, k19, k20,\
    k21, k22, k23, k24, k25 \
) { \
    { k00, k01, k02, k03, k04, k05, k06 }, \
    { k07, k08, k09, k10, k11, k12, k13 }, \
    { k14, k15, k16, k17, k18, k19, k20 }, \
    { k21, k22, k23, k24, k25}, \
}

/*
k22, k23, k24, k09, k10, k03, k12,\
k21, k16, k26, k05, k06, k02, k13,\
k20, k15, k14, k04, k11, k01, k00,\
k19, k17, k18, k07, k08 \
 */
#endif
