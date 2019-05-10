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
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef GLK_HUGO_TYPES
#define GLK_HUGO_TYPES

#include "common/scummsys.h"

namespace Glk {
namespace Hugo {

/**
 * Library/engine globals
 */
enum EngineGlobals {
	object = 0,
	xobject = 1,
	self = 2,
	wordcount = 3,
	player = 4,
	actor = 5,
	location = 6,
	verbroutine = 7,
	endflag = 8,
	prompt = 9,
	objectcount = 10,
	system_status = 11
};

/**
 * Library/engine properties
 */
enum EngineProperties {
	before = 1,
	after = 2,
	noun = 3,
	adjective = 4,
	article = 5
};

/**
 * "display" object properties
 */
enum ObjectProperties {
	screenwidth = 1,
	screenheight = 2,
	linelength = 3,
	windowlines = 4,
	cursor_column = 5,
	cursor_row = 6,
	hasgraphics = 7,
	title_caption = 8,
	hasvideo = 9,
	needs_repaint = 10,
	pointer_x = 11,
	pointer_y = 12
};

/**
 * Fatal errors
 */
enum ERROR_TYPE {
	MEMORY_E = 1,   ///< out of memory
	OPEN_E,         ///< error opening file
	READ_E,         ///< error reading from file
	WRITE_E,        ///< error writing to file
	EXPECT_VAL_E,   ///< expecting value
	UNKNOWN_OP_E,   ///< unknown operation
	ILLEGAL_OP_E,   ///< illegal operation
	OVERFLOW_E,     ///< overflow
	DIVIDE_E		///< divide by zero
};

/**
 * A structure used for disambiguation in MatchObject()
 */
struct pobject_structure {
	int obj;		///< the actual object number
	char type;		///< referred to by noun or adjective

	pobject_structure() : obj(0), type(0) {}
};

/**
 * Structure used for navigating {...} blocks:
 */
struct CODE_BLOCK {
	int type;			///< see #defines, below
	long brk;			///< break address, or 0 to indicate NOP
	long returnaddr;	///< used only for do-while loops

	CODE_BLOCK() : type(0), brk(0), returnaddr(0) {}
};

} // End of namespace Hugo
} // End of namespace Glk

#endif
