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

#ifndef M4_BURGER_ROOMS_SECTION6_ROOM602_H
#define M4_BURGER_ROOMS_SECTION6_ROOM602_H

#include "m4/burger/rooms/room.h"

namespace M4 {
namespace Burger {
namespace Rooms {

class Room602 : public Room {
private:
	noWalkRect *_walk1 = nullptr;
	int _series1 = 0;
	machine *_series2 = nullptr;
	machine *_series3 = nullptr;
	int _series4 = 0;
	int _series5 = 0;
	int _series6 = 0;
	int _series7 = 0;
	machine *_series8 = nullptr;
	int _val1 = 0;
	int _val2 = 0;
	int _val3 = 0;

public:
	Room602() : Room() {}
	~Room602() override {}

	void init() override;
	void daemon() override;
	void pre_parser() override;
	void parser() override;
};

} // namespace Rooms
} // namespace Burger
} // namespace M4

#endif
