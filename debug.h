/*  File: debug.h
 *  
 *  Copyright (C) 2011, Patrick M. Elsen
 *
 *  This file is part of CLists (http://github.com/xfbs/CLists)
 *  Author: Patrick M. Elsen <pelsen.vn (a) gmail.com>
 *
 *  All rights reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


#ifndef _DEBUG_H
#define _DEBUG_H
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

void *log_malloc(size_t size, const char *file, unsigned int line, const char *func);
void log_free(void *data, const char *file, unsigned int line, const char *func);

#ifndef _DEBUG_C
#define malloc(size) log_malloc(size, __FILE__, __LINE__, __func__)
#define free(data) log_free(data, __FILE__, __LINE__, __func__)
#endif

#endif
