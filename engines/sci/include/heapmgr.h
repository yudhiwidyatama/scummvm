/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $URL$
 * $Id$
 *
 */

/* Heap-like managed structure */

#ifndef _FREESCI_HEAPMGR_H_
#define _FREESCI_HEAPMGR_H_

#include "sci/include/resource.h"
#include "sci/include/sci_memory.h"

#define HEAPENTRY_INVALID -1

#define ENTRY_IS_VALID(t, i) ((i) >= 0 && (i) < (t)->max_entry && (t)->table[(i)].next_free == (i))

#define DECLARE_HEAPENTRY(ENTRY)						\
typedef struct {								\
	int next_free; /* Only used for free entries */				\
	ENTRY##_t entry;							\
} ENTRY##_entry_t;								\
										\
typedef struct {								\
	int entries_nr; /* Number of entries allocated */			\
	int first_free; /* Beginning of a singly linked list for entries */	\
	int entries_used; /* Statistical information */				\
	int max_entry; /* Highest entry used */					\
	ENTRY##_entry_t *table;							\
} ENTRY##_table_t;								\
										\
void										\
init_##ENTRY##_table(ENTRY##_table_t *table);					\
int										\
alloc_##ENTRY##_entry(ENTRY##_table_t *table);					\
void										\
free_##ENTRY##_entry(ENTRY##_table_t *table, int index);



#define DEFINE_HEAPENTRY_WITH_CLEANUP(ENTRY, INITIAL, INCREMENT, CLEANUP_FN)	\
void										\
init_##ENTRY##_table(ENTRY##_table_t *table)					\
{										\
	table->entries_nr = INITIAL;						\
	table->max_entry = 0;							\
	table->entries_used = 0;						\
	table->first_free = HEAPENTRY_INVALID;					\
	table->table = (ENTRY##_entry_t*)sci_malloc(sizeof(ENTRY##_entry_t) * INITIAL);\
	memset(table->table, 0, sizeof(ENTRY##_entry_t) * INITIAL);		\
}										\
										\
void										\
free_##ENTRY##_entry(ENTRY##_table_t *table, int index)				\
{										\
	ENTRY##_entry_t *e = table->table + index;				\
										\
	if (index < 0 || index >= table->max_entry) {				\
		fprintf(stderr, "heapmgr: Attempt to release"			\
			" invalid table index %d!\n", index);			\
		BREAKPOINT();							\
	}									\
	CLEANUP_FN(&(e->entry));						\
										\
	e->next_free = table->first_free;					\
	table->first_free = index;						\
	table->entries_used--;							\
}										\
										\
int										\
alloc_##ENTRY##_entry(ENTRY##_table_t *table)					\
{										\
	table->entries_used++;							\
	if (table->first_free != HEAPENTRY_INVALID) {				\
		int oldff = table->first_free;					\
		table->first_free = table->table[oldff].next_free;		\
										\
		table->table[oldff].next_free = oldff;				\
		return oldff;							\
	} else {								\
		if (table->max_entry == table->entries_nr) {			\
			table->entries_nr += INCREMENT;				\
										\
			table->table = (ENTRY##_entry_t*)sci_realloc(table->table,\
						   sizeof(ENTRY##_entry_t)	\
						   * table->entries_nr);	\
			memset(&table->table[table->entries_nr-INCREMENT],	\
			       0, INCREMENT*sizeof(ENTRY##_entry_t));		\
		}								\
		table->table[table->max_entry].next_free =			\
			table->max_entry; /* Tag as 'valid' */			\
		return table->max_entry++;					\
	}									\
}

#define _HEAPENTRY_IGNORE_ME(x)
#define DEFINE_HEAPENTRY(e, i, p) DEFINE_HEAPENTRY_WITH_CLEANUP(e, i, p, _HEAPENTRY_IGNORE_ME)

#endif /* !_FREESCI_HEAPMGR_H_ */
