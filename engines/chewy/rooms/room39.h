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

#ifndef CHEWY_ROOMS_ROOM39_H
#define CHEWY_ROOMS_ROOM39_H

namespace Chewy {
namespace Rooms {

class Room39 {
private:
	static bool _flag;

	static int16 setup_func(int16 frame);
	static void ok();
	static void set_tv();

public:
	static void entry();
	static int16 use_tv();
	static short use_howard();
	static void talk_howard();
	static void look_tv(int16 cls_mode);
};

} // namespace Rooms
} // namespace Chewy

#endif
