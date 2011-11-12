/*  File: llist_node.cpp
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

template<typename data_t>
class LinkedListNode {
public:
	// constructors
	LinkedListNode(LinkedListNode *parent);
	LinkedListNode();
	~LinkedListNode();

	// get the nth node
	node *nthNode(size_t n) const;
	// delete next node
	void deleteNext();

	// vars
	LinkedListNode *next;
	data_t *data;
}

LinkedListNode::LinkedListNode(LinkedListNode *parent) {
	parent->next = this;
	data = 0;
	next = 0;
}

LinkedListNode::LinkedListNode() {
	data = 0;
	next = 0;
}

LinkedListNode::~LinkedListNode() {
	if(data != 0) {
		delete data;
	}
}

LinkedListNode *nthNode(size_t n) const {
	if(n==0) {
		return this;
	} else if(next!=0) {
		return next->nthNode(n-1);
	} else {
		return 0;
	}
}

void LinkedListNode::deleteNext() {
	LinkedListNode *old = next;
	// set the next node to be the one after the next one (skip it)
	next = old->next;
	// delete the old next node (and with it it's data)
	delete old;
}
