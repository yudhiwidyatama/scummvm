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

#include "common/config-manager.h"
#include "engines/util.h"
#include "bagel/console.h"
#include "bagel/spacebar/spacebar.h"
#include "bagel/boflib/app.h"

namespace Bagel {
namespace SpaceBar {

SpaceBarEngine::SpaceBarEngine(OSystem *syst, const ADGameDescription *gameDesc) :
	BagelEngine(syst, gameDesc) {
}

Common::Error SpaceBarEngine::run() {
	// Initialize 320x200 paletted graphics mode
	initGraphics(320, 200);
	_screen = new Graphics::Screen();

	// Set the engine's debugger console
	setDebugger(new Console());

	// Create the app
	CBofApp *pApp = CBofApp::GetApp();
	assert(pApp != nullptr);

	// Initialize
	pApp->PreInit();
	pApp->Initialize();

	// Run the app
	if (!pApp->ErrorOccurred())
		pApp->RunApp();

	// Shutdown
	pApp->PreShutDown();
	pApp->ShutDown();
	pApp->PostShutDown();

	return Common::kNoError;
}

} // namespace SpaceBar
} // namespace Bagel
