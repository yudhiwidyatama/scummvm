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

#include "common/scummsys.h"
#include "common/debug-channels.h"
#include "common/events.h"
#include "common/system.h"
#include "graphics/palette.h"
#include "bagel/bagel.h"
#include "bagel/detection.h"

#include "bagel/baglib/bagel.h"
#include "bagel/baglib/character_object.h"
#include "bagel/baglib/cursor.h"
#include "bagel/baglib/dossier_object.h"
#include "bagel/baglib/event_sdev.h"
#include "bagel/baglib/inv.h"
#include "bagel/baglib/log_msg.h"
#include "bagel/baglib/menu_dlg.h"
#include "bagel/baglib/moo.h"
#include "bagel/baglib/pan_window.h"
#include "bagel/baglib/parse_object.h"
#include "bagel/baglib/pda.h"
#include "bagel/baglib/sound_object.h"
#include "bagel/baglib/storage_dev_win.h"
#include "bagel/baglib/var.h"
#include "bagel/baglib/wield.h"
#include "bagel/baglib/zoom_pda.h"

#include "bagel/boflib/cache.h"
#include "bagel/boflib/error.h"
#include "bagel/boflib/gfx/palette.h"
#include "bagel/boflib/gui/window.h"

namespace Bagel {

BagelEngine *g_engine;

// TODO: Globals needing refactor
BOOL g_bGetVilVars;

BagelEngine::BagelEngine(OSystem *syst, const ADGameDescription *gameDesc) : Engine(syst),
	_gameDescription(gameDesc), _randomSource("Bagel") {
	g_engine = this;

	// baglib/ class statics initializations
	CBagCharacterObject::initStatics();
	CBagCursor::initStatics();
	CBagDossierObject::initStatics();
	CBagEventSDev::initStatics();
	CBagInv::initStatics();
	CBagLog::initStatics();
	CBagMenu::initStatics();
	CBagMenuDlg::initStatics();
	CBagMoo::initStatics();
	CBagPanWindow::initStatics();
	CBagParseObject::initStatics();
	CBagPDA::initStatics();
	CBagSoundObject::initStatics();
	CBagStorageDevWnd::initStatics();
	CBagVarManager::initStatics();
	CBagWield::initStatics();
	CBagel::initStatics();
	SBZoomPda::initStatics();

	// boflib/ class statics initializations
	CCache::initStatics();
	CBofError::initStatics();
	CBofPalette::initStatics();
	CBofWindow::initStatics();
}

BagelEngine::~BagelEngine() {
	delete _screen;
}

uint32 BagelEngine::getFeatures() const {
	return _gameDescription->flags;
}

Common::String BagelEngine::getGameId() const {
	return _gameDescription->gameId;
}

Common::Error BagelEngine::syncGame(Common::Serializer &s) {
	// The Serializer has methods isLoading() and isSaving()
	// if you need to specific steps; for example setting
	// an array size after reading it's length, whereas
	// for saving it would write the existing array's length
	int dummy = 0;
	s.syncAsUint32LE(dummy);

	return Common::kNoError;
}

} // End of namespace Bagel
