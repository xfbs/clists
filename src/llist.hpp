/*  File: linked.hpp
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

#include "llist_node.hpp"

template<typename data_t>
class LinkedList {
	// node data type
	typedef LinkedListNode<data_t> node;

public:
	LinkedList();
	~LinkedList();

	// meta information
	size_t size() const;
	size_t length() const;

	// insertion functions
	void append(data_t *);
	void append(const data_t &);
	void insert(data_t *, size_t);
	void insert(const data_t &, size_t);

	// extraction functions
	data_t &get(size_t pos);

protected:
	node *getNode(size_t pos);

private:
	node *head;
}
