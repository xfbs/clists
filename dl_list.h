/*  File: dl_list.h
 *  Header for dl_list, a C implementation of a double linked list.
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

#ifndef DL_LIST_H
#define DL_LIST_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct dl_list_node
{
    struct dl_list_node *prev;
    void *data;
    struct dl_list_node *next;
};
typedef struct dl_list_node dl_list_node;

struct dl_list
{
    dl_list_node *head;
};
typedef struct dl_list dl_list;

dl_list_node *list_get_node(dl_list *list, size_t pos);
dl_list *dl_list_new();

void list_reset(sl_list *list, int free_data);
void list_delete(sl_list *list, size_t pos, int free_data);
void list_append(sl_list *list, void *data);
void list_insert(sl_list *list, size_t pos, void *data);
void list_debug(sl_list *list);
void list_set(sl_list *list, size_t pos, void *data);
void *list_get(sl_list *list, size_t pos);
void *list_last(sl_list *list);
void *list_first(sl_list *list);
void *list_pop(sl_list *list);
size_t list_size(sl_list *list);

#endif
