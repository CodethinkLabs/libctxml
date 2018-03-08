/* Copyright (c) 2013-17 Codethink Ltd. (http://www.codethink.co.uk)
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

#ifndef __XML_H__
#define __XML_H__

typedef struct
{
	char* name;
	char* data;
} xml_field_t;

typedef struct xml_tag_s xml_tag_t;

struct xml_tag_s
{
	char*         name;
	xml_tag_t*    parent;

	xml_field_t** field;
	unsigned      field_count;

	xml_tag_t**   tag;
	unsigned      tag_count;

	char*         body;
};



xml_tag_t* xml_parse(const char* source);
xml_tag_t* xml_parse_file(const char* path);

const xml_tag_t* xml_tag_tag(const xml_tag_t* tag, const char* name);
const char*      xml_tag_field(const xml_tag_t* tag, const char* name);
const char*      xml_tag_body(const xml_tag_t* tag);

void xml_tag_delete(xml_tag_t* tag);

#endif
