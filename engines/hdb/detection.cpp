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

#include "base/plugins.h"

#include "engines/advancedDetector.h"

#include "hdb/hdb.h"

namespace HDB {
const char *HDBGame::getGameId() const { return _gameDescription->gameId; }
Common::Platform HDBGame::getPlatform() const { return _gameDescription->platform; }

const char *HDBGame::getGameFile() const {
	return _gameDescription->filesDescriptions[0].fileName;
}

uint32 HDBGame::getGameFlags() const {
	return _gameDescription->flags;
}

bool HDBGame::isDemo() const {
	return (getGameFlags() & ADGF_DEMO);
}

} // End of namespace HDB

static const PlainGameDescriptor hdbGames[] = {
	{"hdb", "Hyperspace Delivery Boy!"},
	{0, 0}
};

namespace HDB {
static const ADGameDescription gameDescriptions[] = {
	{
		"hdb",
		"",
		AD_ENTRY1s("hyperspace.mpc", "ff8e51d0872736bc6afe87cfcb846b70", 50339161),
		Common::EN_ANY,
		Common::kPlatformWindows,
		ADGF_NO_FLAGS,
		GUIO1(GUIO_NONE)
	},
	{
		"hdb",
		"",
		AD_ENTRY1s("hyperdemo.mpc", "d8743b3b8be56486bcfb1398b2f2aad4", 13816461),
		Common::EN_ANY,
		Common::kPlatformUnknown,
		ADGF_DEMO,
		GUIO1(GUIO_NONE)
	},
	{
		"hdb",
		"",
		AD_ENTRY1s("hyperdemo.mpc", "f3bc878e179f00b8666a9846f3d9f9f5", 5236568),
		Common::EN_ANY,
		Common::kPlatformUnknown,
		ADGF_DEMO,
		GUIO1(GUIO_NONE)
	},
	// provided by sev
	{
		"hdb",
		"",
		AD_ENTRY1s("hyperdemo.mpc", "7bc533e8f1866931c884f1bc09353744", 13906865),
		Common::EN_ANY,
		Common::kPlatformWindows,
		ADGF_DEMO,
		GUIO1(GUIO_NONE)
	},
	AD_TABLE_END_MARKER
};
} // End of namespace HDB

class HDBMetaEngine : public AdvancedMetaEngine {
public:
	HDBMetaEngine() : AdvancedMetaEngine(HDB::gameDescriptions, sizeof(ADGameDescription), hdbGames) {
		_singleId = "hdb";
	}

	virtual const char *getName() const {
		return "Hyperspace Delivery Boy!";
	}

	virtual const char *getOriginalCopyright() const {
		return "Hyperspace Delivery Boy! (c) 2001 Monkeystone Games";
	}

	virtual bool hasFeature(MetaEngineFeature f) const;
	virtual int getMaximumSaveSlot() const;
	virtual SaveStateList listSaves(const char *target) const;
	virtual bool createInstance(OSystem *syst, Engine **engine, const ADGameDescription *desc) const;
};

bool HDBMetaEngine::hasFeature(MetaEngineFeature f) const {
	return
		(f == kSupportsLoadingDuringStartup) ||
		(f == kSupportsLoadingDuringStartup) ||
		(f == kSupportsListSaves) ||
		(f == kSavesSupportMetaInfo) ||
		(f == kSavesSupportThumbnail) ||
		(f == kSavesSupportPlayTime);
}

bool HDB::HDBGame::hasFeature(Engine::EngineFeature f) const {
	return (f == kSupportsRTL) ||
		   (f == kSupportsLoadingDuringRuntime) ||
		   (f == kSupportsSavingDuringRuntime);
}

int HDBMetaEngine::getMaximumSaveSlot() const { return 9; }

SaveStateList HDBMetaEngine::listSaves(const char *target) const {
	Common::SaveFileManager *saveFileMan = g_system->getSavefileManager();
	Common::StringArray filenames;
	Common::String pattern = target;
	pattern += ".###";

	filenames = saveFileMan->listSavefiles(pattern);

	SaveStateList saveList;
	for (Common::StringArray::const_iterator file = filenames.begin(); file != filenames.end(); ++file) {
		// Obtain the last 2 digits of the filename, since they correspond to the save slot
		int slotNum = atoi(file->c_str() + file->size() - 2);

		if (slotNum >= 0 && slotNum <= getMaximumSaveSlot()) {
			Common::ScopedPtr<Common::InSaveFile> in(saveFileMan->openForLoading(*file));
			if (in) {
				SaveStateDescriptor desc;
				char mapName[32];
				Graphics::Surface *thumbnail;

				if (!Graphics::loadThumbnail(*in, thumbnail)) {
					warning("Error loading thumbnail for %s", file->c_str());
				}
				desc.setThumbnail(thumbnail);

				uint32 timeSeconds = in->readUint32LE();;
				in->read(mapName, 32);

				warning("mapName: %s playtime: %d", mapName, timeSeconds);

				desc.setSaveSlot(slotNum);
				desc.setPlayTime(timeSeconds * 1000);
				desc.setDescription(mapName);

				saveList.push_back(desc);
			}
		}
	}

	// Sort saves based on slot number.
	Common::sort(saveList.begin(), saveList.end(), SaveStateDescriptorSlotComparator());
	return saveList;
}

bool HDBMetaEngine::createInstance(OSystem *syst, Engine **engine, const ADGameDescription *desc) const {
	if (desc) {
		*engine = new HDB::HDBGame(syst, desc);
	}

	return desc != nullptr;
}

#if PLUGIN_ENABLED_DYNAMIC(HDB)
REGISTER_PLUGIN_DYNAMIC(HDB, PLUGIN_TYPE_ENGINE, HDBMetaEngine);
#else
REGISTER_PLUGIN_STATIC(HDB, PLUGIN_TYPE_ENGINE, HDBMetaEngine);
#endif
