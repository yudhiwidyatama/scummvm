/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef M4_PLATFORM_EVENTS_EVENTS_H
#define M4_PLATFORM_EVENTS_EVENTS_H

#include "common/events.h"
#include "m4/m4_types.h"

namespace M4 {

enum mausEvent {
	_ME_no_event,		// 0
	_ME_move,			// 1
	_ME_L_click,		// 2
	_ME_L_hold,			// 3
	_ME_L_drag,			// 4
	_ME_L_release,		// 5
	_ME_R_click,		// 6
	_ME_R_hold,			// 7
	_ME_R_drag,			// 8
	_ME_R_release,		// 9
	_ME_both_click,		// 10
	_ME_both_hold,		// 11
	_ME_both_drag,		// 12
	_ME_both_release,	// 13
	_ME_doubleclick,	// 14
	_ME_doubleclick_hold, // 15
	_ME_doubleclick_drag, // 16
	_ME_doubleclick_release
};

enum mausState {
	_MS_no_event,		// 0
	_MS_L_clickDown,	// 1
	_MS_R_clickDown,	// 2
	_MS_both_clickDown,	// 3
	_MS_doubleclick_Down // 4
};

struct MouseInfo {
	uint16 Event = 0;
	uint16 ButtonState = 0;
	uint16 CursorColumn = 0;	// x
	uint16 CursorRow = 0;		// y
	uint16 HorizontalMickeyCount = 0;
	uint16 VerticalMickeyCount = 0;
};

struct Events : public MouseInfo {
private:
	uint16 &_mouseX = CursorColumn;
	uint16 &_mouseY = CursorRow;
	uint16 _oldX = 0xffff;
	uint16 _oldY = 0xffff;
	mausState _mouse_state = _MS_no_event;
	uint32 _mouseStateEvent = 0;
	uint32 _dclickTime = 0;

	/**
	 * Handles reading in pending events from the ScummVM event queue
	 */
	void pollEvents();

	/**
	 * Handles mouse events
	 */
	void handleMouseEvent(const Common::Event &ev);

	/**
	 * Handles keyboard events
	 */
	void handleKeyboardEvent(const Common::Event &ev);

public:
	Events();
	~Events();

	/**
	 * Updates pending events and timers
	 */
	void process();

	/**
	 * Get the next pending mouse event
	 */
	mausEvent mouse_get_event();
};

extern Events *g_events;

mausEvent mouse_get_event();

} // namespace M4

#endif
