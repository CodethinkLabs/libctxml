/* Copyright (c) 2017 Codethink Ltd. (http://www.codethink.co.uk)
 *
 * This file is part of libctxml.
 *
 * frepo is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * frepo is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libctxml.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef __UTF16_H__
#define __UTF16_H__

#include <stdint.h>
#include <stdbool.h>

char* utf16_decode_bom(const uint16_t* source);
char* utf16_decode(const uint16_t* source, bool big_endian);

#endif
