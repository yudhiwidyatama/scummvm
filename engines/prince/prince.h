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

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef PRINCE_H
#define PRINCE_H

#include "common/random.h"
#include "common/system.h"
#include "common/debug.h"
#include "common/debug-channels.h"
#include "common/textconsole.h"
#include "common/rect.h"
#include "common/events.h"
#include "common/endian.h"

#include "image/bmp.h"

#include "gui/debugger.h"

#include "engines/engine.h"
#include "engines/util.h"

#include "audio/mixer.h"

#include "video/flic_decoder.h"

#include "prince/mob.h"
#include "prince/object.h"
#include "prince/pscr.h"


namespace Prince {

struct PrinceGameDescription;

class PrinceEngine;
class GraphicsMan;
class Script;
class Interpreter;
class InterpreterFlags;
class Debugger;
class MusicPlayer;
class VariaTxt;
class Cursor;
class MhwanhDecoder;
class Font;
class Hero;
class Animation;
class Room;
class Pscr;

struct Text {
	const char *_str;
	uint16 _x, _y;
	uint16 _time;
	uint32 _color;

	Text() : _str(NULL), _x(0), _y(0), _time(0), _color(255){
	}
};

struct AnimListItem {
	uint16 _type; // type of animation - for background anims RND of frame
	uint16 _fileNumber;
	uint16 _startPhase; // first phase number
	uint16 _endPhase;
	uint16 _loopPhase;
	int16 _x;
	int16 _y;
	uint16 _loopType;
	uint16 _nextAnim; // number of animation to do for loop = 3
	uint16 _flags; // byte 0 - draw masks, byte 1 - draw in front of mask, byte 2 - load but turn off drawing
	bool loadFromStream(Common::SeekableReadStream &stream);
};

struct BAS {
	int32 _type; // type of sequence
	int32 _data; // additional data
	int32 _anims; // number of animations
	int32 _current; // actual number of animation
	int32 _counter; // time counter for animation
	int32 _currRelative; //actual relative number for animation
	int32 _data2; // additional data for measurements
};

struct BASA {
	int16 _num;	// animation number
	int16 _start;	// initial frame
	int16 _end;	// final frame
	int16 _pad;	// fulfilment to 8 bytes
};

// background and normal animation
struct Anim {
	BASA _basaData;
	int32 _addr; //animation adress
	int16 _usage;
	int16 _state; // state of animation: 0 - turning on, 1 - turning off
	int16 _flags;
	int16 _frame; // number of phase to show
	int16 _lastFrame; // last phase
	int16 _loopFrame; // first frame of loop
	int16 _showFrame; // actual visible frame of animation
	int16 _loopType;	 // type of loop (0 - last frame; 1 - normal loop (begin from _loopFrame); 2 - no loop; 3 - load new animation)
	int16 _nextAnim; // number of next animation to load after actual
	int16 _x;
	int16 _y;
	int32 _currFrame;
	int16 _currX;
	int16 _currY;
	int16 _currW;
	int16 _currH;
	int16 _packFlag;
	int32 _currShadowFrame;
	int16 _packShadowFlag;
	int32 _shadowBack;
	int16 _relX;
	int16 _relY;
	Animation *_animData;
	Animation *_shadowData;

	enum AnimOffsets {
		kAnimState = 10,
		kAnimFrame = 14,
		kAnimLastFrame = 16,
		kAnimX = 26
	};

	int16 getAnimData(Anim::AnimOffsets offset) {
		switch (offset) {
		case kAnimState:
			return _state;
		case kAnimFrame:
			return _frame;
		case kAnimLastFrame:
			return _lastFrame;
		case kAnimX:
			return _x;
		default:
			error("getAnimData() - Wrong offset type: %d", (int) offset);
		}
	}

	void setAnimData(Anim::AnimOffsets offset, int16 value) {
		if (offset == kAnimX) {
			_x = value;
		} else {
			error("setAnimData() - Wrong offset: %d, value: %d", (int) offset, value);
		}
	}
};

struct BackgroundAnim {
	BAS _seq;
	Common::Array<Anim> backAnims;
};

enum AnimType {
	kBackgroundAnimation,
	kNormalAnimation
};

// Nak (PL - Nakladka)
struct Mask {
	int16 _state; // visible / invisible
	int16 _flags; // turning on / turning off of an mask
	int16 _x1;
	int16 _y1;
	int16 _x2;
	int16 _y2;
	int16 _z;
	int16 _number; // number of mask for background recreating
	int16 _width;
	int16 _height;
	byte *_data;

	int16 getX() const {
		return READ_LE_UINT16(_data);
	}

	int16 getY() const {
		return READ_LE_UINT16(_data + 2);
	}

	int16 getWidth() const {
		return READ_LE_UINT16(_data + 4);
	}

	int16 getHeight() const {
		return READ_LE_UINT16(_data + 6);
	}

	byte *getMask() const {
		return (byte *)(_data + 8);
	}
};

struct InvItem {
	int _x;
	int _y;
	Graphics::Surface *_surface;
	Graphics::Surface *getSurface() const { return _surface; }
};

struct DrawNode {
	int posX;
	int posY;
	int posZ;
	int32 width;
	int32 height;
	Graphics::Surface *s;
	Graphics::Surface *originalRoomSurface;
	byte *data;
	bool freeSurfaceSMemory;
	void (*drawFunction)(Graphics::Surface *, DrawNode *);
};

struct DebugChannel {

enum Type {
	kScript,
	kEngine 
};

};

class PrinceEngine : public Engine {
protected:
	Common::Error run();

public:
	PrinceEngine(OSystem *syst, const PrinceGameDescription *gameDesc);
	virtual ~PrinceEngine();

	virtual bool hasFeature(EngineFeature f) const;

	int getGameType() const;
	const char *getGameId() const;
	uint32 getFeatures() const;
	Common::Language getLanguage() const;

	const PrinceGameDescription *_gameDescription;
	Video::FlicDecoder _flicPlayer;
	VariaTxt *_variaTxt;

	uint32 _talkTxtSize;
	byte *_talkTxt;

	bool loadLocation(uint16 locationNr);
	bool loadAnim(uint16 animNr, bool loop);
	bool loadVoice(uint32 textSlot, uint32 sampleSlot, const Common::String &name);
	bool loadSample(uint32 sampleSlot, const Common::String &name);
	bool loadZoom(byte *zoomBitmap, uint32 dataSize, const char *resourceName);
	bool loadShadow(byte *shadowBitmap, uint32 dataSize, const char *resourceName1, const char *resourceName2);

	void playSample(uint16 sampleId, uint16 loopType);
	void stopSample(uint16 sampleId);

	void setVoice(uint16 slot, uint32 sampleSlot, uint16 flag);

	virtual GUI::Debugger *getDebugger();

	void changeCursor(uint16 curId);
	void printAt(uint32 slot, uint8 color, char *s, uint16 x, uint16 y);
	int calcText(const char *s);

	static const uint8 kMaxTexts = 32;
	Text _textSlots[kMaxTexts];

	uint64 _frameNr;
	Hero *_mainHero;
	Hero *_secondHero;

	int _mouseFlag;
	uint16 _locationNr;
	uint16 _sceneWidth;
	int32 _picWindowX;
	int32 _picWindowY;
	Image::BitmapDecoder *_roomBmp;
	MhwanhDecoder *_suitcaseBmp;
	Room *_room;
	Script *_script;

	static const int kMaxNormAnims = 64;
	static const int kMaxBackAnims = 64;
	static const int kMaxObjects = 64;

	Common::Array<AnimListItem> _animList;
	Common::Array<BackgroundAnim> _backAnimList;
	Common::Array<Anim> _normAnimList;
	Common::Array<Mob> _mobList;
	Common::Array<Mask> _maskList;
	Common::Array<Object *> _objList;
	int *_objSlot;

	void freeNormAnim(int slot);
	void freeAllNormAnims();
	void removeSingleBackAnim(int slot);

	Common::RandomSource _randomSource;

	static const int16 kNormalWidth = 640;
	static const int16 kNormalHeight = 480;
	static const int16 kMaxPicWidth = 1280;
	static const int16 kMaxPicHeight = 480;

	void checkMasks(int x1, int y1, int sprWidth, int sprHeight, int z);
	void insertMasks(Graphics::Surface *originalRoomSurface);
	void showMask(int maskNr, Graphics::Surface *originalRoomSurface);
	void clsMasks();

	int _selectedMob; // number of selected Mob / inventory item
	int _selectedItem; // number of item on mouse cursor
	int _selectedMode;
	int _currentPointerNumber;

	static const int16 kMaxInv = 90; // max amount of inventory items in whole game
	static const int16 kMaxItems = 30; // size of inventory

	uint32 _invTxtSize;
	byte *_invTxt;

	Graphics::Surface *_optionsPic;
	Graphics::Surface *_optionsPicInInventory;

	bool _optionsFlag;
	int _optionEnabled;
	int _optionsMob;
	int _optionsX;
	int _optionsY;
	int _optionsWidth;
	int _optionsHeight;
	int _invOptionsWidth;
	int _invOptionsHeight;
	int _optionsStep;
	int _invOptionsStep;
	int _optionsNumber;
	int _invOptionsNumber;
	int _optionsColor1; // color for non-selected options
	int _optionsColor2; // color for selected option

	bool _showInventoryFlag;
	int _invExamY;
	bool _inventoryBackgroundRemember;
	int _invLineX;
	int _invLineY;
	int _invLine;  // number of items in one line
	int _invLines; // number of lines with inventory items
	int _invLineW;
	int _invLineH;
	int _maxInvW;
	int _maxInvH;
	int _invLineSkipX;
	int _invLineSkipY;
	int _invX1;
	int _invY1;
	int _invWidth;
	int _invHeight;
	bool _invCurInside;
	int _mst_shadow;
	int _mst_shadow2; // blinking after adding new item
	int _candleCounter; // special counter for candle inventory item
	int _invMaxCount; // time to turn inventory on
	int _invCounter; // turning on counter

	void inventoryFlagChange(bool inventoryState);
	bool loadAllInv();
	void rememberScreenInv();
	void prepareInventoryToView();
	void drawInvItems();
	void displayInventory();
	void addInv(int hero, int item, bool addItemQuiet);
	void remInv(int hero, int item);
	void clearInv(int hero);
	void swapInv(int hero);
	void checkInv(int hero, int item);
	void addInvObj();
	void makeInvCursor(int itemNr);
	void enableOptions();
	void checkOptions();
	void checkInvOptions();

	void leftMouseButton();
	void rightMouseButton();
	void inventoryLeftMouseButton();
	void inventoryRightMouseButton();
	void dialogLeftMouseButton(byte *string, int dialogSelected);

	uint32 _dialogDatSize;
	byte *_dialogDat;
	byte *_dialogData; // on, off flags for lines of dialog text

	byte *_dialogBoxAddr[32]; // adresses of dialog windows
	byte *_dialogOptAddr[32]; // adresses of dialog options
	int _dialogOptLines[4 * 32]; // numbers of initial dialog lines

	byte *_dialogText;
	int _dialogLines;
	bool _dialogFlag;
	int _dialogWidth;
	int _dialogHeight;
	int _dialogLineSpace;
	int _dialogColor1; // color for non-selected options
	int _dialogColor2; // color for selected option
	Graphics::Surface *_dialogImage;

	void createDialogBox(int dialogBoxNr);
	void runDialog();
	void talkHero(int slot);
	void doTalkAnim(int animNumber, int slot, AnimType animType);

	void initZoomIn(int slot);
	void initZoomOut(int slot);

	// Pathfinding
	static const int16 kPathGridStep = 2;
	static const int32 kPathBitmapLen = (kMaxPicHeight / kPathGridStep * kMaxPicWidth / kPathGridStep) / 8;
	static const int32 kTracePts = 8000;
	static const int32 kPBW = kMaxPicWidth / 16; // PathBitmapWidth
	byte *_roomPathBitmap; // PL - Sala
	byte *_roomPathBitmapTemp; // PL -SSala

	int _destX;
	int _destY;
	int _destX2;
	int _destY2;
	int _fpFlag;
	int _fpX;
	int _fpY;
	int _fpX1;
	int _fpY1;
	Direction _direction;
	byte *_coordsBufEnd;
	byte *_coordsBuf; // optimal path
	byte *_coords; // last path point adress from coordsBuf
	byte *_coordsBuf2;
	byte *_coords2;
	byte *_coordsBuf3;
	byte *_coords3;
	int _traceLineLen;
	int _traceLineFlag; // return value of plotTraceLine
	bool _traceLineFirstPointFlag; // if plotTraceLine after first point
	int _tracePointFlag; // return value of plotTracePoint
	byte *_directionTable;
	int _shanLen1;

	byte *_checkBitmapTemp; //esi
	byte *_checkBitmap; // ebp
	int _checkMask; // dl
	int _checkX; // eax
	int _checkY; // ebx

	byte *_rembBitmapTemp; // esi
	byte *_rembBitmap; // ebp
	int _rembMask; // dl
	int _rembX; // eax
	int _rembY;  // ebx

	struct fpResult {
		int x1;
		int y1;
		int x2;
		int y2;
	} _fpResult;

	bool loadPath(const char *resourceName);
	byte *makePath(int destX, int destY);
	void findPoint(int x1, int y1, int x2, int y2);
	int fpGetPixelAddr(int x, int y);
	int fpGetPixel(int x, int y);
	int getPixelAddr(byte *pathBitmap, int x, int y);
	static void plotTraceLine(int x, int y, int color, void *data);
	void specialPlotInside(int x, int y);
	int tracePath(int x1, int y1, int x2, int y2);
	Direction makeDirection(int x1, int y1, int x2, int y2);
	void specialPlot(int x, int y);
	void specialPlot2(int x, int y);
	void allocCoords2();
	void freeCoords2();
	void freeCoords3();
	static void plotTracePoint(int x, int y, int color, void *data);
	void specialPlotInside2(int x, int y);
	void approxPath();
	void freeDirectionTable();
	void scanDirections();
	int scanDirectionsFindNext(byte *coords, int xDiff, int yDiff);
	void moveShandria();

	void testDrawPath();

	int leftDownDir();
	int leftDir();
	int leftUpDir();
	int rightDownDir();
	int rightDir();
	int rightUpDir();
	int upLeftDir();
	int upDir();
	int upRightDir();
	int downLeftDir();
	int downDir();
	int downRightDir();

	int cpe();
	int checkLeftDownDir();
	int checkLeftDir();
	int checkDownDir();
	int checkUpDir();
	int checkRightDir();
	int checkLeftUpDir();
	int checkRightDownDir();
	int checkRightUpDir();

	int testAnimNr;
	int testAnimFrame;

private:
	bool playNextFrame();
	void keyHandler(Common::Event event);
	int checkMob(Graphics::Surface *screen, Common::Array<Mob> &mobList);
	void drawScreen();
	void showTexts(Graphics::Surface *screen);
	void init();
	void showLogo();
	void showAnim(Anim &anim);
	void showNormAnims();
	void setBackAnim(Anim &backAnim);
	void showBackAnims();
	void clearBackAnimList();
	bool spriteCheck(int sprWidth, int sprHeight, int destX, int destY);
	void showSprite(Graphics::Surface *spriteSurface, int destX, int destY, int destZ, bool freeSurfaceMemory);
	void showSpriteShadow(Graphics::Surface *shadowSurface, int destX, int destY, int destZ, bool freeSurfaceMemory);
	void showObjects();
	void showParallax();
	static bool compareDrawNodes(DrawNode d1, DrawNode d2);
	void runDrawNodes();
	void freeDrawNodes();
	void makeShadowTable(int brightness);
	void pause();

	uint32 getTextWidth(const char *s);
	void debugEngine(const char *s, ...);

	uint8 _cursorNr;

	Common::RandomSource *_rnd;
	Cursor *_cursor1;
	Graphics::Surface *_cursor2;
	Cursor *_cursor3;
	Debugger *_debugger;
	GraphicsMan *_graph;
	InterpreterFlags *_flags;
	Interpreter *_interpreter;
	Font *_font;
	MusicPlayer *_midiPlayer;

	static const uint32 MAX_SAMPLES = 60;	
	Common::SeekableReadStream *_voiceStream[MAX_SAMPLES];
	Audio::SoundHandle _soundHandle[MAX_SAMPLES];

	Common::Array<PScr *> _pscrList;
	Common::Array<DrawNode> _drawNodeList;
	Common::Array<InvItem> _allInvList;
	Common::Array<Mob> _invMobList;

	bool _flicLooped;
	
	void mainLoop();

};

} // End of namespace Prince

#endif

/* vim: set tabstop=4 noexpandtab: */
