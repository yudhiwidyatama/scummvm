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

#ifndef GLK_SCOTT_DETECTGAME
#define GLK_SCOTT_DETECTGAME

#include "common/stream.h"
#include "glk/scott/definitions.h"
#include "glk/scott/types.h"

namespace Glk {
namespace Scott {

void readHeader(uint8_t *ptr);
int parseHeader(int *h, HeaderType type, int *ni, int *na, int *nw, int *nr, int *mc, int *pr, int *tr, int *wl, int *lt, int *mn, int *trm);
GameIDType detectGame(Common::SeekableReadStream *f);
uint8_t *seekToPos(uint8_t *buf, size_t offset);
int seekIfNeeded(int expectedStart, int *offset, uint8_t **ptr);
int tryLoading(GameInfo info, int dictStart, int loud);
DictionaryType getId(int *offset);
int findCode(const char *x, int base);

} // End of namespace Scott
} // End of namespace Glk

#endif
