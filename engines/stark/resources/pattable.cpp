/* ResidualVM - A 3D game interpreter
 *
 * ResidualVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the AUTHORS
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

#include "engines/stark/resources/pattable.h"
#include "engines/stark/resources/script.h"

#include "engines/stark/formats/xrc.h"

namespace Stark {
namespace Resources {

PATTable::~PATTable() {
}

PATTable::PATTable(Object *parent, byte subType, uint16 index, const Common::String &name) :
				Object(parent, subType, index, name),
				_field_2C(-1) {
	_type = TYPE;
}

void PATTable::readData(Formats::XRCReadStream *stream) {
	uint32 entryCount = stream->readUint32LE();
	for (uint i = 0; i < entryCount; i++) {
		Entry entry;

		entry._actionType = stream->readSint32LE();
		entry._scriptIndex = stream->readSint32LE();

		_entries.push_back(entry);
	}

	_field_2C = stream->readSint32LE();
}

void PATTable::printData() {
	for (uint i = 0; i < _entries.size(); i++) {
		debug("entry[%d].actionType: %d", i, _entries[i]._actionType);
		debug("entry[%d].scriptIndex: %d", i, _entries[i]._scriptIndex);
	}
	debug("field_2C: %d", _field_2C);
}

ActionArray PATTable::listPossibleActions() const {
	ActionArray actions;

	for (uint i = 0; i < _entries.size(); i++) {
		if (_entries[i]._scriptIndex != -1) {
			// Check the script can be launched
			Script *script = findChildWithIndex<Script>(_entries[i]._scriptIndex);
			if (script->shouldExecute(Script::kCallModePlayerAction)) {
				actions.push_back(_entries[i]._actionType);
			}
		}
	}

	return actions;
}

bool PATTable::canPerformAction(uint32 action) const {
	for (uint i = 0; i < _entries.size(); i++) {
		if (_entries[i]._actionType == action && _entries[i]._scriptIndex != -1) {
			return true;
		}
	}
	return false;
}

bool PATTable::runScriptForAction(uint32 action) {
	for (uint i = 0; i < _entries.size(); i++) {
		if (_entries[i]._actionType == action) {
			Script *script = findChildWithIndex<Script>(_entries[i]._scriptIndex);
			script->execute(Script::kCallModePlayerAction);
		}
	}

	return false;
}

} // End of namespace Resources
} // End of namespace Stark
