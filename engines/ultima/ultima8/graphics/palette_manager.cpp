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

#include "ultima/ultima8/misc/debugger.h"

#include "ultima/ultima8/graphics/palette_manager.h"
#include "ultima/ultima8/graphics/palette.h"
#include "ultima/ultima8/graphics/texture.h"

namespace Ultima {
namespace Ultima8 {

PaletteManager *PaletteManager::_paletteManager = nullptr;

PaletteManager::PaletteManager(const Graphics::PixelFormat &format) : _format(format) {
	debugN(MM_INFO, "Creating PaletteManager...\n");

	_paletteManager = this;
}

PaletteManager::~PaletteManager() {
	reset();
	debugN(MM_INFO, "Destroying PaletteManager...\n");
	_paletteManager = nullptr;
}

// Reset the Palette Manager
void PaletteManager::reset() {
	debugN(MM_INFO, "Resetting PaletteManager...\n");

	for (unsigned int i = 0; i < _palettes.size(); ++i)
		delete _palettes[i];
	_palettes.clear();
}

void PaletteManager::updatedPalette(PalIndex index, int maxindex) {
	Palette *pal = getPalette(index);
	if (pal)
		createNativePalette(pal, maxindex, _format);
}

// Reset all the transforms back to default
void PaletteManager::resetTransforms() {
	debugN(MM_INFO, "Resetting Palette Transforms...\n");

	int16 matrix[12];
	getTransformMatrix(matrix, Transform_None);

	for (unsigned int i = 0; i < _palettes.size(); ++i) {
		Palette *pal = _palettes[i];
		if (!pal) continue;
		pal->_transform = Transform_None;
		for (int j = 0; j < 12; j++)
			pal->_matrix[j] = matrix[j];
		createNativePalette(pal, 0, _format); // convert to native format
	}
}

bool PaletteManager::loadTransforms(Common::ReadStream& rs) {
	int16 matrix[12];
	for (int i = 0; i < 12; i++)
		matrix[i] = rs.readUint16LE();

	PaletteManager::get_instance()->transformPalette(PaletteManager::Pal_Game, matrix);
	Palette *pal = getPalette(PaletteManager::Pal_Game);
	pal->_transform = static_cast<PalTransforms>(rs.readUint16LE());

	if (pal->_transform >= Transform_Invalid) {
		warning("Invalid palette transform %d.  Corrupt savegame?", static_cast<int>(pal->_transform));
		return false;
	}
	return true;
}

void PaletteManager::saveTransforms(Common::WriteStream& ws) {
	Palette *pal = getPalette(PaletteManager::Pal_Game);
	for (int i = 0; i < 12; i++)
		ws.writeUint16LE(pal->_matrix[i]);
	ws.writeUint16LE(pal->_transform);
}

void PaletteManager::PixelFormatChanged(const Graphics::PixelFormat &format) {
	_format = format;

	// Create native _palettes for all currently loaded _palettes
	for (unsigned int i = 0; i < _palettes.size(); ++i)
		if (_palettes[i])
			createNativePalette(_palettes[i], 0, _format);
}

void PaletteManager::load(PalIndex index, Common::ReadStream &rs, Common::ReadStream &xformrs) {
	if (_palettes.size() <= static_cast<unsigned int>(index))
		_palettes.resize(index + 1);

	if (_palettes[index])
		delete _palettes[index];

	Palette *pal = new Palette;
	pal->load(rs, xformrs);
	createNativePalette(pal, 0, _format); // convert to native format

	_palettes[index] = pal;
}

void PaletteManager::load(PalIndex index, Common::ReadStream &rs) {
	if (_palettes.size() <= static_cast<unsigned int>(index))
		_palettes.resize(index + 1);

	if (_palettes[index])
		delete _palettes[index];

	Palette *pal = new Palette;
	pal->load(rs);
	createNativePalette(pal, 0, _format); // convert to native format

	_palettes[index] = pal;
}

void PaletteManager::duplicate(PalIndex src, PalIndex dest) {
	Palette *newpal = getPalette(dest);
	if (!newpal)
		newpal = new Palette;
	Palette *srcpal = getPalette(src);
	if (srcpal)
		*newpal = *srcpal;

	createNativePalette(newpal, 0, _format); // convert to native format
	if (_palettes.size() <= static_cast<unsigned int>(dest))
		_palettes.resize(dest + 1);
	_palettes[dest] = newpal;
}

Palette *PaletteManager::getPalette(PalIndex index) {
	if (static_cast<unsigned int>(index) >= _palettes.size())
		return nullptr;

	return _palettes[index];
}

void PaletteManager::transformPalette(PalIndex index, const int16 matrix[12]) {
	Palette *pal = getPalette(index);

	if (!pal) return;

	for (int i = 0; i < 12; i++)
		pal->_matrix[i] = matrix[i];
	createNativePalette(pal, 0, _format); // convert to native format
}

void PaletteManager::untransformPalette(PalIndex index) {
	Palette *pal = getPalette(index);

	if (!pal) return;

	pal->_transform = Transform_None;
	int16 matrix[12];
	getTransformMatrix(matrix, Transform_None);
	transformPalette(index, matrix);
}

bool PaletteManager::getTransformMatrix(int16 matrix[12], PalIndex index) {
	Palette *pal = getPalette(index);

	if (!pal) return false;

	for (int i = 0; i < 12; i++)
		matrix[i] = pal->_matrix[i];
	return true;
}

void PaletteManager::getTransformMatrix(int16 matrix[12], PalTransforms trans) {
	switch (trans) {
	// Normal untransformed palette
	case Transform_None: {
		matrix[0] = 0x800;
		matrix[1] = 0;
		matrix[2]  = 0;
		matrix[3]  = 0;
		matrix[4] = 0;
		matrix[5] = 0x800;
		matrix[6]  = 0;
		matrix[7]  = 0;
		matrix[8] = 0;
		matrix[9] = 0;
		matrix[10] = 0x800;
		matrix[11] = 0;
	}
	break;

	// O[i] = I[r]*0.375 + I[g]*0.5 + I[b]*0.125;
	case Transform_Greyscale: {
		for (int i = 0; i < 3; i++) {
			matrix[i * 4 + 0] = 0x0300;
			matrix[i * 4 + 1] = 0x0400;
			matrix[i * 4 + 2] = 0x0100;
			matrix[i * 4 + 3] = 0;
		}
	}
	break;

	// O[r] = 0;
	case Transform_NoRed: {
		matrix[0] = 0;
		matrix[1] = 0;
		matrix[2] = 0;
		matrix[3] = 0;
		matrix[4] = 0;
		matrix[5] = 0x800;
		matrix[6] = 0;
		matrix[7] = 0;
		matrix[8] = 0;
		matrix[9] = 0;
		matrix[10] = 0x800;
		matrix[11] = 0;
	}
	break;

	// O[i] = (I[i] + Grey)*0.25 + 0.1875;
	case Transform_RainStorm: {
		for (int i = 0; i < 3; i++) {
			matrix[i * 4 + 0] = (0x0300 * 0x0200) >> 11;
			matrix[i * 4 + 1] = (0x0400 * 0x0200) >> 11;
			matrix[i * 4 + 2] = (0x0100 * 0x0200) >> 11;

			matrix[i * 4 + i] += 0x0200;

			matrix[i * 4 + 3] = 0x0180;
		}
	}
	break;

	// O[r] = I[r]*0.5 + Grey*0.5  + 0.1875;
	// O[g] = I[g]*0.5 + Grey*0.25;
	// O[b] = I[b]*0.5;
	case Transform_FireStorm: {
		// O[r] = I[r]*0.5 + Grey*0.5 + 0.1875;
		matrix[0] = ((0x0300 * 0x0400) >> 11) + 0x0400;
		matrix[1] = (0x0400 * 0x0400) >> 11;
		matrix[2] = (0x0100 * 0x0400) >> 11;
		matrix[3]  = 0x0180;

		// O[g] = I[g]*0.5 + Grey*0.25;
		matrix[4] = (0x0300 * 0x0200) >> 11;
		matrix[5] = ((0x0400 * 0x0200) >> 11) + 0x0400;
		matrix[6] = (0x0100 * 0x0200) >> 11;
		matrix[7]  = 0;

		// O[b] = I[b]*0.5;
		matrix[8]  = 0;
		matrix[9]  = 0;
		matrix[10] = 0x0400;
		matrix[11] = 0;
	}
	break;

	// O[i] = I[i]*2 -Grey;
	case Transform_Saturate: {
		for (int i = 0; i < 3; i++) {
			matrix[i * 4 + 0] = -0x0300;
			matrix[i * 4 + 1] = -0x0400;
			matrix[i * 4 + 2] = -0x0100;
			matrix[i * 4 + 3] = 0;
			matrix[i * 4 + i] += 0x1000;
		}
	}
	break;

	// O[b] = I[r]; O[r] = I[g]; O[g] = I[b];
	case Transform_BRG: {
		matrix[0] = 0;
		matrix[1] = 0x800;
		matrix[2] = 0;
		matrix[3] = 0;
		matrix[4] = 0;
		matrix[5] = 0;
		matrix[6] = 0x800;
		matrix[7] = 0;
		matrix[8] = 0x800;
		matrix[9] = 0;
		matrix[10] = 0;
		matrix[11] = 0;
	}
	break;

	// O[g] = I[r]; O[b] = I[g]; O[r] = I[b];
	case Transform_GBR: {
		matrix[0] = 0;
		matrix[1] = 0;
		matrix[2] = 0x800;
		matrix[3] = 0;
		matrix[4] = 0x800;
		matrix[5] = 0;
		matrix[6] = 0;
		matrix[7] = 0;
		matrix[8] = 0;
		matrix[9] = 0x800;
		matrix[10] = 0;
		matrix[11] = 0;
	}
	break;

	// Unknown
	default: {
		warning("Unknown Palette Transformation: %d", trans);
		matrix[0] = 0x800;
		matrix[1] = 0;
		matrix[2] = 0;
		matrix[3] = 0;
		matrix[4] = 0;
		matrix[5] = 0x800;
		matrix[6] = 0;
		matrix[7] = 0;
		matrix[8] = 0;
		matrix[9] = 0;
		matrix[10] = 0x800;
		matrix[11] = 0;
	}
	break;
	}
}


void PaletteManager::getTransformMatrix(int16 matrix[12], uint32 col32) {
	matrix[0]  = (static_cast<int32>(TEX32_A(col32)) * 0x800) / 255;
	matrix[1]  = 0;
	matrix[2]  = 0;
	matrix[3]  = (static_cast<int32>(TEX32_R(col32)) * 0x800) / 255;

	matrix[4]  = 0;
	matrix[5]  = (static_cast<int32>(TEX32_A(col32)) * 0x800) / 255;
	matrix[6]  = 0;
	matrix[7]  = (static_cast<int32>(TEX32_G(col32)) * 0x800) / 255;

	matrix[8]  = 0;
	matrix[9]  = 0;
	matrix[10] = (static_cast<int32>(TEX32_A(col32)) * 0x800) / 255;
	matrix[11] = (static_cast<int32>(TEX32_B(col32)) * 0x800) / 255;
}

void PaletteManager::createNativePalette(Palette *palette, int maxindex, const Graphics::PixelFormat &format) {
	if (maxindex == 0)
		maxindex = 256;
	for (int i = 0; i < maxindex; i++) {
		int32 r, g, b;
		byte sr, sg, sb;

		// Normal palette
		palette->get(i, sr, sg, sb);
		palette->_native_untransformed[i] = format.RGBToColor(sr, sg, sb);

		r = palette->_matrix[0] * sr +
			palette->_matrix[1] * sg +
			palette->_matrix[2] * sb +
			palette->_matrix[3] * 255;
		if (r < 0)
			r = 0;
		if (r > 0x7F800)
			r = 0x7F800;

		g = palette->_matrix[4] * sr +
			palette->_matrix[5] * sg +
			palette->_matrix[6] * sb +
			palette->_matrix[7] * 255;
		if (g < 0)
			g = 0;
		if (g > 0x7F800)
			g = 0x7F800;

		b = palette->_matrix[8] * sr +
			palette->_matrix[9] * sg +
			palette->_matrix[10] * sb +
			palette->_matrix[11] * 255;
		if (b < 0)
			b = 0;
		if (b > 0x7F800)
			b = 0x7F800;

		// Transformed normal palette
		palette->_native[i] = format.RGBToColor(static_cast<uint8>(r >> 11),
												static_cast<uint8>(g >> 11),
												static_cast<uint8>(b >> 11));

		// Transformed XFORM palette (Uses the TEX32 format)
		if (TEX32_A(palette->_xform_untransformed[i])) {
			r = palette->_matrix[0] * TEX32_R(palette->_xform_untransformed[i]) +
				palette->_matrix[1] * TEX32_G(palette->_xform_untransformed[i]) +
				palette->_matrix[2] * TEX32_B(palette->_xform_untransformed[i]) +
				palette->_matrix[3] * 255;
			if (r < 0)
				r = 0;
			if (r > 0x7F800)
				r = 0x7F800;

			g = palette->_matrix[4] * TEX32_R(palette->_xform_untransformed[i]) +
				palette->_matrix[5] * TEX32_G(palette->_xform_untransformed[i]) +
				palette->_matrix[6] * TEX32_B(palette->_xform_untransformed[i]) +
				palette->_matrix[7] * 255;
			if (g < 0)
				g = 0;
			if (g > 0x7F800)
				g = 0x7F800;

			b = palette->_matrix[8] * TEX32_R(palette->_xform_untransformed[i]) +
				palette->_matrix[9] * TEX32_G(palette->_xform_untransformed[i]) +
				palette->_matrix[10] * TEX32_B(palette->_xform_untransformed[i]) +
				palette->_matrix[11] * 255;
			if (b < 0)
				b = 0;
			if (b > 0x7F800)
				b = 0x7F800;

			palette->_xform[i] = TEX32_PACK_RGBA(static_cast<uint8>(r >> 11),
												 static_cast<uint8>(g >> 11),
												 static_cast<uint8>(b >> 11),
												 TEX32_A(palette->_xform_untransformed[i]));
		} else
			palette->_xform[i] = 0;
	}
}

} // End of namespace Ultima8
} // End of namespace Ultima
