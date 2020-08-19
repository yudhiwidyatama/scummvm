
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

#include "common/scummsys.h"

#if defined(SDL_BACKEND)

#include "backends/timer/sdl/sdl-timer.h"

#include "common/textconsole.h"

static volatile bool timerInstalled = false;

static Uint32 timer_handler(Uint32 interval, void *param) {
	if (!timerInstalled) {
#ifdef DIRECTORBUILDBOT
		warning("timer_handler: timer is not installed");
#endif
		return interval;
	}

#ifdef DIRECTORBUILDBOT
	warning("timer_handler: called");
#endif

	((DefaultTimerManager *)param)->handler();
	return interval;
}

SdlTimerManager::SdlTimerManager() {
	// Initializes the SDL timer subsystem
	if (SDL_InitSubSystem(SDL_INIT_TIMER) == -1) {
		error("Could not initialize SDL: %s", SDL_GetError());
	}

	timerInstalled = true;

	// Creates the timer callback
	_timerID = SDL_AddTimer(10, &timer_handler, this);
}

SdlTimerManager::~SdlTimerManager() {
#ifdef DIRECTORBUILDBOT
	warning("~SdlTimerManager");
#endif
	timerInstalled = false;
	// Removes the timer callback
	SDL_RemoveTimer(_timerID);

#ifdef DIRECTORBUILDBOT
	warning("~SdlTimerManager: SDL timer removed");
#endif
}

#endif
