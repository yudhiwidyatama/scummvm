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

#ifndef MTROPOLIS_ASSETS_H
#define MTROPOLIS_ASSETS_H

#include "mtropolis/data.h"
#include "mtropolis/runtime.h"
#include "mtropolis/render.h"

namespace Audio {
} // End of namespace Audio

namespace MTropolis {

struct AssetLoaderContext;
struct AudioMetadata;
class AudioPlayer;

class ColorTableAsset : public Asset {
public:
	bool load(AssetLoaderContext &context, const Data::ColorTableAsset &data);
	AssetType getAssetType() const override;

private:
	ColorRGB8 _colors[256];
};

class CachedAudio {
public:
	CachedAudio();

	bool loadFromStream(const AudioMetadata &metadata, Common::ReadStream *stream, size_t size);

	const void *getData() const;
	size_t getSize() const;

	size_t getNumSamples(const AudioMetadata &metadata) const;

private:
	Common::Array<uint8> _data;
};

struct AudioMetadata {
	struct CuePoint {
		uint32 position;
		uint32 cuePointID;
	};

	enum Encoding {
		kEncodingUncompressed,
		kEncodingMace3,
		kEncodingMace6,
	};

	Encoding encoding;
	uint32 durationMSec;
	uint16 sampleRate;
	uint8 channels;
	uint8 bitsPerSample;
	bool isBigEndian;

	Common::Array<CuePoint> cuePoints;
};

class AudioAsset : public Asset {
public:
	bool load(AssetLoaderContext &context, const Data::AudioAsset &data);
	AssetType getAssetType() const override;

	size_t getStreamIndex() const;
	const Common::SharedPtr<AudioMetadata> &getMetadata() const;

	const Common::SharedPtr<CachedAudio> &loadAndCacheAudio(Runtime *runtime);

private:
	uint32 _filePosition;
	uint32 _size;

	size_t _streamIndex;

	Common::SharedPtr<CachedAudio> _audioCache;
	Common::SharedPtr<AudioMetadata> _metadata;
};

class MovieAsset : public Asset {
public:
	bool load(AssetLoaderContext &context, const Data::MovieAsset &data);
	AssetType getAssetType() const override;

	uint32 getMovieDataPos() const;
	uint32 getMoovAtomPos() const;
	uint32 getMovieDataSize() const;

	const Common::String &getExtFileName() const;
	size_t getStreamIndex() const;

private:
	uint32 _movieDataPos;
	uint32 _moovAtomPos;
	uint32 _movieDataSize;

	Common::String _extFileName;
	size_t _streamIndex;
};

class CachedImage {
public:
	CachedImage();

	const Common::SharedPtr<Graphics::Surface> &optimize(Runtime *runtime);

	void resetSurface(ColorDepthMode colorDepth, const Common::SharedPtr<Graphics::Surface> &surface);

private:
	Common::SharedPtr<Graphics::Surface> _surface;
	Common::SharedPtr<Graphics::Surface> _optimizedSurface;

	ColorDepthMode _colorDepth;
	bool _isOptimized;
};

class ImageAsset : public Asset {
public:
	ImageAsset();
	~ImageAsset();

	bool load(AssetLoaderContext &context, const Data::ImageAsset &data);
	AssetType getAssetType() const override;

	enum ImageFormat {
		kImageFormatMac,
		kImageFormatWindows,
	};

	const Rect16 &getRect() const;
	ColorDepthMode getColorDepth() const;
	uint32 getFilePosition() const;
	uint32 getSize() const;
	size_t getStreamIndex() const;
	ImageFormat getImageFormat() const;

	const Common::SharedPtr<CachedImage> &loadAndCacheImage(Runtime *runtime);

private:
	Rect16 _rect;
	ColorDepthMode _colorDepth;
	uint32 _filePosition;
	uint32 _size;
	size_t _streamIndex;
	ImageFormat _imageFormat;

	Common::SharedPtr<CachedImage> _imageCache;
};


struct MToonAsset : public Asset {
public:
	bool load(AssetLoaderContext &context, const Data::MToonAsset &data);
	AssetType getAssetType() const override;

	enum ImageFormat {
		kImageFormatMac,
		kImageFormatWindows,
	};

	struct FrameDef {
		Rect16 rect;
		uint32 dataOffset;
		uint32 compressedSize;
		uint32 decompressedSize;
		uint16 decompressedBytesPerRow;
		bool isKeyFrame;

		bool load(AssetLoaderContext &context, const Data::MToonAsset::FrameDef &data);
	};

	struct FrameRangeDef {
		uint32 startFrame;
		uint32 endFrame;

		Common::String name;

		bool load(AssetLoaderContext &context, const Data::MToonAsset::FrameRangeDef &data);
	};

private:
	ImageFormat _imageFormat;

	uint32 _frameDataPosition;
	uint32 _sizeOfFrameData;

	Rect16 _rect;
	uint16 _bitsPerPixel;
	uint32 _codecID;

	Common::Array<FrameDef> _frames;
	Common::Array<FrameRangeDef> _frameRanges;
	Common::Array<uint8> _codecData;
};

class TextAsset : public Asset {
public:
	bool load(AssetLoaderContext &context, const Data::TextAsset &data);
	AssetType getAssetType() const override;

	bool isBitmap() const;
	const Common::SharedPtr<Graphics::Surface> &getBitmapSurface() const;
	const Common::String &getString() const;
	const Common::Array<MacFormattingSpan> &getMacFormattingSpans() const;

private:
	Rect16 _bitmapRect;
	TextAlignment _alignment;
	bool _isBitmap;

	Common::SharedPtr<Graphics::Surface> _bitmapData;
	Common::String _stringData;

	Common::Array<MacFormattingSpan> _macFormattingSpans;
};

} // End of namespace MTropolis

#endif
