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

#include "chewy/dialogs/cinema.h"
#include "chewy/events.h"
#include "chewy/file.h"
#include "chewy/globals.h"
#include "chewy/main.h"
#include "chewy/sound.h"

namespace Chewy {
namespace Dialogs {

static constexpr int CINEMA_LINES = 12;

static const int16 CINEMA_TBL[4 * 3] = {
	10,  80,  32, 105,
	10, 150,  32, 175,
	36,  64, 310, 188
};

static const uint8 CINEMA_FLICS[35] = {
	FCUT_000, FCUT_002, FCUT_006, FCUT_009, FCUT_015,
	FCUT_012, FCUT_011, FCUT_SPACECHASE_18, FCUT_003, FCUT_048,
	FCUT_031, FCUT_044, FCUT_055, FCUT_058, FCUT_045,
	FCUT_065, FCUT_067, FCUT_068, FCUT_069, FCUT_080,
	FCUT_074, FCUT_083, FCUT_084, FCUT_088, FCUT_093,
	FCUT_087, FCUT_106, FCUT_108, FCUT_107, FCUT_113,
	FCUT_110, FCUT_121, FCUT_123, FCUT_122, FCUT_117
};

void Cinema::execute() {
	int16 txt_anz = 0;
	int topIndex = 0;
	int selected = -1;
	bool flag = false;
	int delay = 0;
	Common::Array<int> cutscenes;
	getCutscenes(cutscenes);

	_G(fontMgr)->setFont(_G(font6));
	_G(atds)->load_atds(98, 1);

	_G(room)->open_handle(GBOOK, 0);
	_G(room)->load_tgp(4, &_G(room_blk), 1, 0, GBOOK);
	showCur();
	EVENTS_CLEAR;
	_G(kbinfo).scan_code = 0;

	for (bool endLoop = false; !endLoop;) {
		_G(out)->setPointer(_G(workptr));
		_G(out)->map_spr2screen(_G(ablage)[_G(room_blk).AkAblage], 0, 0);

		if (!cutscenes.empty()) {
			// Render cut-scene list
			for (int i = 0; i < CINEMA_LINES; ++i) {
				char *csName = _G(atds)->ats_get_txt(546 + i + topIndex,
					0, &txt_anz, 1);
				int yp = i * 10 + 68;

				if (i == selected)
					_G(out)->boxFill(37, yp, 308, yp + 10, 42);
				_G(out)->printxy(40, yp, 14, 300, 0, csName);
			}
		} else {
			// No cut-scene seen yet
			char *none = _G(atds)->ats_get_txt(545, 0, &txt_anz, 1);
			_G(out)->printxy(40, 68, 14, 300, _G(scr_width), none);
		}

		if (_G(minfo)._button == 1 && !flag) {
			flag = true;
			switch (_G(in)->mouseVector(_G(minfo).x, _G(minfo).y, CINEMA_TBL, 3)) {
			case 0:
				_G(kbinfo).scan_code = Common::KEYCODE_UP;
				if (!endLoop)
					endLoop = true;

				break;

			case 1:
				_G(kbinfo).scan_code = Common::KEYCODE_DOWN;
				if (!endLoop)
					endLoop = true;

				break;

			case 2:
			{
				int selIndex = (_G(minfo).y - 68) / 10 + topIndex;
				if (selIndex < (int)cutscenes.size())
					selected = selIndex;
				_G(kbinfo).scan_code = Common::KEYCODE_RETURN;
				break;
			}

			default:
				break;
			}
		} else if (_G(minfo)._button == 2 && !flag) {
			_G(kbinfo).scan_code = Common::KEYCODE_ESCAPE;
			flag = true;
		} else if (_G(minfo)._button != 1) {
			flag = false;
			delay = 0;
		} else if (flag) {
			g_events->update(true);
			if (--delay <= 0)
				flag = false;
		}

		switch (_G(kbinfo).scan_code) {
		case Common::KEYCODE_ESCAPE:
			endLoop = true;
			_G(kbinfo).scan_code = 0;
			break;

		case Common::KEYCODE_UP:
		case Common::KEYCODE_KP8:
			if (selected > 0) {
				--selected;
			} else if (topIndex > 0) {
				--topIndex;
			}
			_G(kbinfo).scan_code = 0;
			break;

		case Common::KEYCODE_DOWN:
		case Common::KEYCODE_KP2:
		{
			int newIndex = selected + 1;
			if (selected >= 11) {
				if ((topIndex + newIndex) < (int)cutscenes.size())
					++topIndex;
			} else {
				if ((topIndex + newIndex) < (int)cutscenes.size())
					++selected;
			}
			_G(kbinfo).scan_code = 0;
			break;
		}

		case Common::KEYCODE_RETURN:
			hideCur();
			_G(out)->cls();
			_G(out)->setPointer(_G(screen0));
			_G(fx)->blende1(_G(workptr), _G(screen0), _G(pal), 150, 0, 0);
			print_rows(546 + topIndex);

			_G(flc)->set_custom_user_function(cut_serv);
			flic_cut(CINEMA_FLICS[topIndex + selected]);
			_G(flc)->remove_custom_user_function();
			_G(fontMgr)->setFont(_G(font6));
			showCur();
			delay = 0;
			flag = false;
			break;

		default:
			break;
		}

		// The below are hacks to get the dialog to work in ScummVM
		_G(kbinfo).scan_code = 0;
		_G(minfo)._button = 0;
		txt_anz = 0;

		if (!txt_anz) {
			_G(cur)->plot_cur();

			if (flag) {
				flag = false;
				_G(out)->setPointer(_G(screen0));
				_G(room)->set_ak_pal(&_G(room_blk));
				_G(fx)->blende1(_G(workptr), _G(screen0), _G(pal), 150, 0, 0);
			} else {
				_G(out)->back2screen(_G(workpage));
			}
		}

		g_events->update(true);
		SHOULD_QUIT_RETURN;
	}

	_G(room)->open_handle(EPISODE1, 0);
	_G(room)->set_ak_pal(&_G(room_blk));
	hideCur();
	_G(uhr)->resetTimer(0, 5);
}

int16 Cinema::cut_serv(int16 frame) {
	if (_G(in)->getSwitchCode() == Common::KEYCODE_ESCAPE) {
		_G(sndPlayer)->stopMod();
		g_engine->_sound->stopAllSounds();
		return -1;
	}

	return 0;
}

} // namespace Dialogs
} // namespace Chewy
