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

#include "utf16.h"

#include <stdlib.h>



char* utf16_decode_bom(const uint16_t* source)
{
	if (!source)
		return NULL;


	if (source[0] == 0xFEFF)
		return utf16_decode(&source[1], false);
	else if (source[0] == 0xFFFE)
		return utf16_decode(&source[1], true);

	return NULL;
}

static uint16_t endian_swap16(uint16_t a)
{
	return ((a << 8) | (a >> 8));
}

char* utf16_decode(const uint16_t* source, bool big_endian)
{
	if (!source) return NULL;

	unsigned max;
	for (max = 0; source[max] != 0; max++);

	char* result = (char*)malloc((max * 5) + 1);
	if (!result) return NULL;

	unsigned i, s;
	for (i = 0, s = 0; i < max; i++)
	{
		uint32_t c = source[i];
		if (big_endian) c = endian_swap16(c);

		if ((c >= 0xD800) && (c <= 0xDFFF))
		{
			uint16_t d = source[++i];
			if (big_endian) d = endian_swap16(d);

			if ((d < 0xD800) || (d > 0xDFFF))
			{
				free(result);
				return NULL;
			}

			c = ((c - 0xD800) << 10) + (d - 0xDC00);
		}

		if (c <= 0x7F)
		{
			result[s++] = c;
		}
		else if (c <= 0x7FF)
		{
			result[s++] = 0x80 | ( c       & 0x3F);
			result[s++] = 0xC0 | ((c >> 6) & 0x1F);
		}
		else if (c <= 0xFFFF)
		{
			result[s++] = 0x80 | ( c        & 0x3F);
			result[s++] = 0x80 | ((c >>  6) & 0x3F);
			result[s++] = 0xE0 | ((c >> 12) & 0x0F);
		}
		else if (c <= 0x10FFFF)
		{
			result[s++] = 0x80 | ( c        & 0x3F);
			result[s++] = 0x80 | ((c >>  6) & 0x3F);
			result[s++] = 0x80 | ((c >> 12) & 0x3F);
			result[s++] = 0xF0 | ((c >> 18) & 0x07);
		}
		else
		{
			free(result);
			return NULL;
		}
	}

	result[s] = 0x00;
	if (s < max)
	{
		char* nresult = (char*)realloc(result, (s + 1));
		if (nresult) result = nresult;
	}

	return result;	
}
