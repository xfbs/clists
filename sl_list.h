/*  File: sl_list.h
 *  Header for sl_list, a C implementation of a single linked list.
 *  
 *  Copyright (C) 2011, Patrick M. Elsen
 *
 *  This file is part of CMatrixCrypt (http://github.com/xfbs/CMatrixCrypt)
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

#ifndef SL_LIST_H
#define SL_LIST_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "list.h"

struct sl_list_node
{
    void *data;
    struct sl_list_node *next;
};
typedef struct sl_list_node sl_list_node;

struct sl_list
{
    sl_list_node *head;
};
typedef struct sl_list sl_list;

sl_list_node *list_get_node(sl_list *list, size_t pos);
sl_list *sl_list_new();
void list_reset(sl_list *list, bool free_data);
void list_delete(sl_list *list, bool free_data);
void list_append(sl_list *list, void *data);
void list_debug(sl_list *list);
void list_set(sl_list *list, size_t pos, void *data);
void *list_get(sl_list *list, size_t pos);
void *list_last(sl_list *list);
void *list_first(sl_list *list);
void *list_pop(sl_list *list);
size_t list_size(sl_list *list);

#endif
