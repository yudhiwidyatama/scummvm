#include "common/scummsys.h"

#include "audio/decoders/wave.h"
#include "audio/audiostream.h"

#include "common/archive.h"
#include "common/config-manager.h"
#include "common/debug.h"
#include "common/debug-channels.h"
#include "common/error.h"
#include "common/events.h"
#include "common/file.h"
#include "common/fs.h"
#include "common/system.h"
#include "common/str.h"
#include "common/savefile.h"
#include "engines/util.h"

#include "image/bmp.h"
#include "graphics/cursorman.h"

#include "private/cursors.h"
#include "private/private.h"
#include "private/grammar.tab.h"
#include "private/grammar.h"


namespace Private {

PrivateEngine *g_private = NULL;

extern int parse(char*);

PrivateEngine::PrivateEngine(OSystem *syst)
    : Engine(syst) {
    // Put your engine in a sane state, but do nothing big yet;
    // in particular, do not load data from files; rather, if you
    // need to do such things, do them from run().

    // Do not initialize graphics here
    // Do not initialize audio devices here

    // However this is the place to specify all default directories
    //SearchMan.addSubDirectoryMatching(gameDataDir, "global", 0, 10, false);

    // Here is the right place to set up the engine specific debug channels
    //DebugMan.addDebugChannel(kPrivateDebugExample, "example", "this is just an example for a engine specific debug channel");
    //DebugMan.addDebugChannel(kPrivateDebugExample2, "example2", "also an example");

    // Don't forget to register your random source
    _rnd = new Common::RandomSource("private");

    g_private = this;

    _saveGameMask = NULL;
    _loadGameMask = NULL;

    _nextSetting = NULL;
    _currentSetting = NULL;
    _nextMovie = NULL;
    _nextVS = NULL;
    _modified = false;
    _mode = -1;
    _toTake = false;
    _frame = new Common::String("inface/general/inface2.bmp");
    _repeatedMovieExit = new Common::String("");
    _pausedSetting = NULL;


    _policeBustEnabled = false;
    _policeBustSetting = NULL;
    _numberClicks = 0;
    policeVideoIndex = 0;

    _paperShuffleSound = new Common::String("global/audio/glsfx0");
    _takeSound = new Common::String("global/audio/took");
    _leaveSound = new Common::String("global/audio/left");
    _sirenSound = new Common::String("po/audio/posfx002.wav");

    _policeRadioArea = NULL;
    _AMRadioArea = NULL;
    _phoneArea = NULL;

    // TODO: use this as a default sound for radio
    _radioSound = new Common::String("inface/radio/radio.wav");

    _AMRadioPrefix = new Common::String("inface/radio/comm_/");
    _policeRadioPrefix = new Common::String("inface/radio/police/");
    _phonePrefix = new Common::String("inface/telephon/");
    _phoneCallSound = new Common::String("phone.wav");

}

PrivateEngine::~PrivateEngine() {
    debug("PrivateEngine::~PrivateEngine");

    // Dispose your resources here
    delete _rnd;

    // Remove all of our debug levels here
    DebugMan.clearAllDebugChannels();
}

void PrivateEngine::initializePath(const Common::FSNode &gamePath) {
    SearchMan.addDirectory(gamePath.getPath(), gamePath, 0, 10);
}

Common::Error PrivateEngine::run() {

    assert(_installerArchive.open("SUPPORT/ASSETS.Z"));
    Common::SeekableReadStream *file = NULL;

    // if the full game is used
    if (_installerArchive.hasFile("GAME.DAT"))
        file = _installerArchive.createReadStreamForMember("GAME.DAT");

    // if the demo from archive.org is used
    else if (_installerArchive.hasFile("GAME.TXT"))
        file = _installerArchive.createReadStreamForMember("GAME.TXT");

    // if the demo from the full retail CDROM is used
    else if (_installerArchive.hasFile("DEMOGAME.DAT"))
        file = _installerArchive.createReadStreamForMember("DEMOGAME.DAT");

    assert(file != NULL);
    void *buf = malloc(191000);
    file->read(buf, 191000);

    // Initialize stuff
    initInsts();
    initFuncs();
    initCursors();

    parse((char *) buf);
    assert(constants.size() > 0);

    // Initialize graphics using following:
    _screenW = 640;
    _screenH = 480;
    //_pixelFormat = Graphics::PixelFormat::createFormatCLUT8();
    _pixelFormat = Graphics::PixelFormat(4, 8, 8, 8, 8, 24, 16, 8, 0);
    _transparentColor = _pixelFormat.RGBToColor(0,255,0);
    initGraphics(_screenW, _screenH, &_pixelFormat);
    changeCursor("default");

    _origin = new Common::Point(0, 0);
    _image = new Image::BitmapDecoder();
    _compositeSurface = new Graphics::ManagedSurface();
    _compositeSurface->create(_screenW, _screenH, _pixelFormat);
    _compositeSurface->setTransparentColor(_transparentColor);

    // Create debugger console. It requires GFX to be initialized
    Console *console = new Console(this);
    setDebugger(console);

    // Additional setup.
    debug("PrivateEngine::init");

    // Simple main event loop
    Common::Event event;
    Common::Point mousePos;
    _videoDecoder = nullptr; //new Video::SmackerDecoder();

    int saveSlot = ConfMan.getInt("save_slot");
    if (saveSlot >= 0) { // load the savegame
        loadGameState(saveSlot);
    } else {
        _nextSetting = &kGoIntro;
    }

    while (!shouldQuit()) {
        checkPhoneCall();

        while (g_system->getEventManager()->pollEvent(event)) {
            mousePos = g_system->getEventManager()->getMousePos();
            // Events
            switch (event.type) {
            case Common::EVENT_KEYDOWN:
                if (event.kbd.keycode == Common::KEYCODE_ESCAPE && _videoDecoder)
                    skipVideo();
                else if (event.kbd.keycode == Common::KEYCODE_m) {
                    if ( _pausedSetting == NULL) {
                        _pausedSetting = _currentSetting;
                        _nextSetting = &kPauseMovie;
                    }
                }
                else if (event.kbd.keycode == Common::KEYCODE_p) {
                    debug("Number of clicks %d", _numberClicks);

                }
                break;

            case Common::EVENT_QUIT:
            case Common::EVENT_RETURN_TO_LAUNCHER:
                break;

            case Common::EVENT_LBUTTONDOWN:
                _numberClicks++; 
                selectPhoneArea(mousePos);
                selectPoliceRadioArea(mousePos);
                selectAMRadioArea(mousePos);
                selectLoadGame(mousePos);
                selectSaveGame(mousePos);
                selectMask(mousePos);
                if (!_nextSetting)
                    selectExit(mousePos);
                break;

            case Common::EVENT_MOUSEMOVE:
                changeCursor("default");
                if (cursorMask(mousePos))      {}
                else if (cursorExit(mousePos))     {}
                //
                break;

            default:
            {}

            }
        }

        checkPoliceBust();

        // Movies
        if (_nextMovie != NULL) {
            _videoDecoder = new Video::SmackerDecoder();
            playVideo(*_nextMovie);
            _nextMovie = NULL;
            continue;

        }

        if (_nextVS != NULL) {
            loadImage(*_nextVS, 160, 120, true);
            _nextVS = NULL;
        }

        if (_videoDecoder) {

            stopSound();
            if (_videoDecoder->endOfVideo()) {
                _videoDecoder->close();
                delete _videoDecoder;
                _videoDecoder = nullptr;
            } else if (_videoDecoder->needsUpdate()) {
                drawScreen();
            }
            continue;
        }

        if (_nextSetting != NULL) {
            debug("Executing %s", _nextSetting->c_str());
            _exits.clear();
            _masks.clear();
            _loadGameMask = NULL;
            _saveGameMask = NULL;
            _policeRadioArea = NULL;
            _policeRadioArea = NULL;
            _AMRadioArea = NULL;
            _phoneArea = NULL;
            _currentSetting = _nextSetting;
            loadSetting(_nextSetting);
            _nextSetting = NULL;
            execute(prog);
            changeCursor("default");
        }

        g_system->updateScreen();
        g_system->delayMillis(10);
    }

    return Common::kNoError;
}

void PrivateEngine::startPoliceBust() {
    Common::String k("kPoliceIndex");
    int policeIndex = variables.getVal(k)->u.val;

    int r = _rnd->getRandomNumber(0xc);
    if (0x14 < policeIndex) {
        policeIndex = 0x15;
    }
    _maxNumberClicks = r + 0x10 + (policeIndex * 0xe) / -0x15;
    _sirenWarning = 3 + _rnd->getRandomNumber(0x7);
    _numberClicks = 0;
    assert(_sirenWarning < _maxNumberClicks);
}

void PrivateEngine::checkPoliceBust() {
    if (!_policeBustEnabled)
        return;

    if (_numberClicks < _sirenWarning)
        return;
     
    if (_numberClicks == _sirenWarning) {
        stopSound(); 
        playSound(*_sirenSound, 0);
        _numberClicks++; // Won't execute again
        return;
    }

    if (_numberClicks == _maxNumberClicks+1) {
        Common::String k("kPoliceIndex");
        uint kPoliceIndex = variables.getVal(k)->u.val;

        if (kPoliceIndex <= 12) {
            assert(policeVideoIndex/2 <= 5);
            char f[30];
            sprintf(f, "po/animatio/spoc%02dxs.smk", kPoliceBustVideos[policeVideoIndex/2]);
            policeVideoIndex++;

            Common::String *pv = new Common::String(f);
            _nextMovie = pv;
        }
        _policeBustSetting = _currentSetting;
        _nextSetting = &kPoliceBustFromMO;
        _numberClicks++; // Won't execute again
    }

}


bool PrivateEngine::cursorExit(Common::Point mousePos) {
    //debug("Mousepos %d %d", mousePos.x, mousePos.y);
    mousePos = mousePos - *_origin;
    if (mousePos.x < 0 || mousePos.y < 0)
        return false;

    int rs = 100000000;
    int cs = 0;
    ExitInfo e;
    Common::String *cursor = NULL;

    for (ExitList::iterator it = _exits.begin(); it != _exits.end(); ++it) {
        e = *it;
        cs = e.rect->width()*e.rect->height();

        if (e.rect->contains(mousePos)) {
            if (cs < rs && e.cursor != NULL) {
                rs = cs;
                cursor = e.cursor;
            }

        }
    }

    if (cursor != NULL) {
        changeCursor(*cursor);
        return true;
    }

    return false;
}

bool PrivateEngine::inMask(Graphics::ManagedSurface *surf, Common::Point mousePos) {
    if (surf == NULL)
        return false;

    mousePos = mousePos - *_origin;
    if (mousePos.x < 0 || mousePos.y < 0)
        return false;

    if (mousePos.x > surf->w || mousePos.y > surf->h)
        return false;

    return ( *((uint32*) surf->getBasePtr(mousePos.x, mousePos.y)) != _transparentColor);
}


bool PrivateEngine::cursorMask(Common::Point mousePos) {
    //debug("Mousepos %d %d", mousePos.x, mousePos.y);
    MaskInfo m;
    bool inside = false;
    for (MaskList::iterator it = _masks.begin(); it != _masks.end(); ++it) {
        m = *it;

        if (inMask(m.surf, mousePos)) {
            //debug("Inside!");
            if (m.cursor != NULL) { // TODO: check this
                inside = true;
                //debug("Rendering cursor mask %s", m.cursor->c_str());
                changeCursor(*m.cursor);
                break;
            }

        }
    }
    return inside;
}

void PrivateEngine::selectExit(Common::Point mousePos) {
    //debug("Mousepos %d %d", mousePos.x, mousePos.y);
    mousePos = mousePos - *_origin;
    if (mousePos.x < 0 || mousePos.y < 0)
        return;

    Common::String *ns = NULL;
    int rs = 100000000;
    int cs = 0;
    ExitInfo e;
    for (ExitList::iterator it = _exits.begin(); it != _exits.end(); ++it) {
        e = *it;
        cs = e.rect->width()*e.rect->height();
        //debug("Testing exit %s %d", e.nextSetting->c_str(), cs);
        if (e.rect->contains(mousePos)) {
            //debug("Inside! %d %d", cs, rs);
            if (cs < rs && e.nextSetting != NULL) { // TODO: check this
                // an item was not taken
                if (_toTake) {
                    playSound(* getLeaveSound(), 1);
                    _toTake = false;
                }

                //debug("Found Exit %s %d", e.nextSetting->c_str(), cs);
                rs = cs;
                ns = e.nextSetting;
            }

        }
    }
    if (ns != NULL) {
        //debug("Exit selected %s", ns->c_str());
        _nextSetting = ns;
    }
}

void PrivateEngine::selectMask(Common::Point mousePos) {
    Common::String *ns = NULL;
    MaskInfo m;
    for (MaskList::iterator it = _masks.begin(); it != _masks.end(); ++it) {
        m = *it;

        //debug("Testing mask %s", m.nextSetting->c_str());
        if (inMask(m.surf, mousePos)) {
            //debug("Inside!");
            if (m.nextSetting != NULL) { // TODO: check this
                //debug("Found Mask %s", m.nextSetting->c_str());
                ns = m.nextSetting;
            }

            if (m.flag1 != NULL) { // TODO: check this
                setSymbol(m.flag1, 1);
                debug("!!!!!!!!!!!!!! setting %s to 1 !!!!!!!!!!!!!!!!!!1", m.flag1->name->c_str());
                // an item was taken
                if (_toTake) {
                    playSound(*getTakeSound(), 1);
                    _toTake = false;
                }
            }

            if (m.flag2 != NULL) {
                setSymbol(m.flag2, 1);
            }

            break;

        }
    }
    if (ns != NULL) {
        //debug("Mask selected %s", ns->c_str());
        _nextSetting = ns;
    }
}

void PrivateEngine::selectAMRadioArea(Common::Point mousePos) {
    if (_AMRadioArea == NULL)
        return;

    if (_AMRadio.empty())
        return;

    debug("AMRadio");
    if (inMask(_AMRadioArea->surf, mousePos)) {
        Common::String sound = *_AMRadioPrefix + _AMRadio.back() + ".wav";
        playSound(sound.c_str(), 1);
        _AMRadio.pop_back();
    }

}

void PrivateEngine::selectPoliceRadioArea(Common::Point mousePos) {
    if (_policeRadioArea == NULL)
        return;

    if (_policeRadio.empty())
        return;

    debug("PoliceRadio");
    if (inMask(_policeRadioArea->surf, mousePos)) {
        Common::String sound = *_policeRadioPrefix + _policeRadio.back() + ".wav";
        playSound(sound.c_str(), 1);
        _policeRadio.pop_back();
    }

}

void PrivateEngine::checkPhoneCall() {
    if (_phoneArea == NULL)
        return;

    if (_phone.empty())
        return;

    if (!_mixer->isSoundHandleActive(_soundHandle))
        playSound(*_phonePrefix + *_phoneCallSound, 1);

}

void PrivateEngine::selectPhoneArea(Common::Point mousePos) {
    if (_phoneArea == NULL)
        return;

    if (_phone.empty())
        return;

    debug("Phone");
    if (inMask(_phoneArea->surf, mousePos)) {
        PhoneInfo i = _phone.back();
        Common::String sound(*i.sound);
        setSymbol(i.flag, i.val);
        sound = *_phonePrefix + sound + ".wav";
        playSound(sound.c_str(), 1);
        _phone.pop_back();
    }

}


void PrivateEngine::selectLoadGame(Common::Point mousePos) {
    if (_loadGameMask == NULL)
        return;

    if (inMask(_loadGameMask->surf, mousePos)) {
        loadGameDialog();
    }
}

void PrivateEngine::selectSaveGame(Common::Point mousePos) {
    if (_saveGameMask == NULL)
        return;

    if (inMask(_saveGameMask->surf, mousePos)) {
        saveGameDialog();
    }

}

bool PrivateEngine::hasFeature(EngineFeature f) const {
    return
        (f == kSupportsReturnToLauncher);
}

void PrivateEngine::restartGame() {
    debug("restartGame");

    for (VariableList::iterator it = variableList.begin(); it != variableList.end(); ++it) {
        Private::Symbol *sym = variables.getVal(*it);
        if (strcmp("kAlternateGame", sym->name->c_str()) != 0)
            sym->u.val = 0;
    }
    // TODO: reset sound lists
}

Common::Error PrivateEngine::loadGameStream(Common::SeekableReadStream *stream) {
    Common::Serializer s(stream, nullptr);
    debug("loadGameStream");
    _nextSetting = &kMainDesktop;
    int val;

    for (VariableList::iterator it = variableList.begin(); it != variableList.end(); ++it) {
        s.syncAsUint32LE(val);
        Private::Symbol *sym = variables.getVal(*it);
        sym->u.val = val;
    }

    uint32 size = 0;
    Common::String *sound;
    size = stream->readUint32LE();
    debug("AMRadio size %d", size);
    _AMRadio.clear();

    for (uint32 i = 0; i < size; ++i) {
        sound = new Common::String(stream->readString());
        debug("sound: %s", sound->c_str());
        _AMRadio.push_back(*sound);
    }

    size = stream->readUint32LE();
    debug("policeRadio size %d", size);
    _policeRadio.clear();

    for (uint32 i = 0; i < size; ++i) {
        sound = new Common::String(stream->readString());
        debug("sound: %s", sound->c_str());
        _policeRadio.push_back(*sound);
    }

    size = stream->readUint32LE();
    _phone.clear();

    for (uint32 j = 0; j < size; ++j) {
        PhoneInfo *i = (PhoneInfo*) malloc(sizeof(PhoneInfo));

        i->sound = new Common::String(stream->readString());
        i->flag  = variables.getVal(stream->readString());
        i->val   = stream->readUint32LE();
        _phone.push_back(*i);
    }

    *_repeatedMovieExit = stream->readString();

    _playedMovies.clear();
    size = stream->readUint32LE();
    Common::String *movie;

    for (uint32 i = 0; i < size; ++i) {
        movie = new Common::String(stream->readString());
        _playedMovies.setVal(*movie, true);
    }

    _playedPhoneClips.clear();
    size = stream->readUint32LE();
    Common::String *phone;

    for (uint32 i = 0; i < size; ++i) {
        phone = new Common::String(stream->readString());
        _playedPhoneClips.setVal(*phone, true);
    }

    //syncGameStream(s);
    return Common::kNoError;
}

Common::Error PrivateEngine::saveGameStream(Common::WriteStream *stream, bool isAutosave) {
    debug("saveGameStream %d", isAutosave);
    if (isAutosave)
        return Common::kNoError;

    for (VariableList::iterator it = variableList.begin(); it != variableList.end(); ++it) {
        Private::Symbol *sym = variables.getVal(*it);
        stream->writeUint32LE(sym->u.val);
    }

    stream->writeUint32LE(_AMRadio.size());
    for (SoundList::iterator it = _AMRadio.begin(); it != _AMRadio.end(); ++it) {
        stream->writeString(*it);
        stream->writeByte(0);
    }

    stream->writeUint32LE(_policeRadio.size());
    for (SoundList::iterator it = _policeRadio.begin(); it != _policeRadio.end(); ++it) {
        stream->writeString(*it);
        stream->writeByte(0);
    }

    stream->writeUint32LE(_phone.size());
    for (PhoneList::iterator it = _phone.begin(); it != _phone.end(); ++it) {
        //PhoneInfo *i = *it;
        stream->writeString(*it->sound);
        stream->writeByte(0);
        stream->writeString(*it->flag->name);
        stream->writeByte(0);
        stream->writeUint32LE(it->val);
    }

    stream->writeString(*_repeatedMovieExit);
    stream->writeByte(0);

    stream->writeUint32LE(_playedMovies.size());
    for (PlayedMediaTable::iterator it = _playedMovies.begin(); it != _playedMovies.end(); ++it) {
        stream->writeString(it->_key);
        stream->writeByte(0);
    }

    stream->writeUint32LE(_playedPhoneClips.size());
    for (PlayedMediaTable::iterator it = _playedPhoneClips.begin(); it != _playedPhoneClips.end(); ++it) {
        stream->writeString(it->_key);
        stream->writeByte(0);
    }

    return Common::kNoError;
}

void PrivateEngine::syncGameStream(Common::Serializer &s) {
    debug("syncGameStream");
    // Use methods of Serializer to save/load fields
    //int dummy = 0;
    //s.syncString(*_currentSetting);
}

Common::String PrivateEngine::convertPath(Common::String name) {
    Common::String path(name);
    Common::String s1("\\");
    Common::String s2("/");

    while (path.contains(s1))
        Common::replace(path, s1, s2);

    s1 = Common::String("\"");
    s2 = Common::String("");

    Common::replace(path, s1, s2);
    Common::replace(path, s1, s2);

    path.toLowercase();
    return path;
}

void PrivateEngine::playSound(const Common::String &name, uint loops) {
    debugC(1, kPrivateDebugExample, "%s : %s", __FUNCTION__, name.c_str());

    Common::File *file = new Common::File();
    Common::String path = convertPath(name);

    if (!file->open(path))
        error("unable to find sound file %s", path.c_str());

    Audio::LoopingAudioStream *stream;
    stream = new Audio::LoopingAudioStream(Audio::makeWAVStream(file, DisposeAfterUse::YES), loops);
    stopSound();
    _mixer->playStream(Audio::Mixer::kSFXSoundType, &_soundHandle, stream, -1, Audio::Mixer::kMaxChannelVolume);
}

void PrivateEngine::playVideo(const Common::String &name) {
    debug("%s : %s", __FUNCTION__, name.c_str());
    Common::File *file = new Common::File();
    Common::String path = convertPath(name);

    if (!file->open(path))
        error("unable to find video file %s", path.c_str());

    if (!_videoDecoder->loadStream(file))
        error("unable to load video %s", path.c_str());
    _videoDecoder->start();

}

void PrivateEngine::skipVideo() {
    _videoDecoder->close();
    delete _videoDecoder;
    _videoDecoder = nullptr;
}


void PrivateEngine::stopSound() {
    debugC(3, kPrivateDebugExample, "%s", __FUNCTION__);
    if (_mixer->isSoundHandleActive(_soundHandle))
        _mixer->stopHandle(_soundHandle);
}

void PrivateEngine::loadImage(const Common::String &name, int x, int y, bool drawn) {
    debugC(1, kPrivateDebugExample, "%s : %s", __FUNCTION__, name.c_str());
    Common::File file;
    Common::String path = convertPath(name);
    if (!file.open(path))
        error("unable to load image %s", path.c_str());

    _image->loadStream(file);
    _compositeSurface->transBlitFrom(*_image->getSurface()->convertTo(_pixelFormat, _image->getPalette()), *_origin + Common::Point(x,y), _transparentColor);
    drawScreen();
}

void PrivateEngine::drawScreenFrame(Graphics::Surface *screen) {
    Common::String path = convertPath(*_frame);
    Common::File file;
    assert(file.open(path));
    _image->loadStream(file);
    Graphics::Surface *frame = _image->getSurface()->convertTo(_pixelFormat, _image->getPalette());
    screen->copyRectToSurface(*frame, 0, 0, Common::Rect(0, 0, _screenW, _screenH));
    frame->free();
    delete frame;
}


Graphics::ManagedSurface *PrivateEngine::loadMask(const Common::String &name, int x, int y, bool drawn) {
    debugC(1, kPrivateDebugExample, "%s : %s", __FUNCTION__, name.c_str());
    Common::File file;
    Common::String path = convertPath(name);
    if (!file.open(path))
        error("unable to load mask %s", path.c_str());

    _image->loadStream(file);
    Graphics::ManagedSurface *surf = new Graphics::ManagedSurface();
    surf->create(_screenW, _screenH, _pixelFormat);
    surf->transBlitFrom(*_image->getSurface()->convertTo(_pixelFormat, _image->getPalette()), Common::Point(x,y));

    if (drawn) {
        _compositeSurface->transBlitFrom(surf->rawSurface(), *_origin + Common::Point(x,y), _transparentColor);
        drawScreen();
    }

    return surf;
}

void PrivateEngine::drawScreen() {
    Graphics::Surface *screen = g_system->lockScreen();
    Graphics::ManagedSurface *surface = _compositeSurface;
    int w = surface->w;
    int h = surface->h;

    if (_videoDecoder) {
        Graphics::Surface *frame = new Graphics::Surface;
        frame->create(_screenW, _screenH, _pixelFormat);
        frame->copyFrom(*_videoDecoder->decodeNextFrame());
        Graphics::Surface *cframe = frame->convertTo(_pixelFormat, _videoDecoder->getPalette());
        surface->transBlitFrom(*cframe, *_origin);
        frame->free();
        cframe->free();
        delete frame;
        delete cframe;
    }

    assert(w == _screenW && h == _screenH);

    if (_mode == 1) {
        drawScreenFrame(screen);
    }
    Common::Rect window(_origin->x, _origin->y, _screenW - _origin->x, _screenH - _origin->y);
    screen->copyRectToSurface(*surface, _origin->x, _origin->y, window);
    g_system->unlockScreen();
    //if (_image->getPalette() != nullptr)
    //    g_system->getPaletteManager()->setPalette(_image->getPalette(), _image->getPaletteStartIndex(), _image->getPaletteColorCount());
    g_system->updateScreen();

}

bool PrivateEngine::getRandomBool(uint p) {
    uint r = _rnd->getRandomNumber(100);
    return (r <= p);
}

Common::String *PrivateEngine::getPaperShuffleSound() {
    uint r = 32 + _rnd->getRandomNumber(7);

    // there is no global/audio/glsfx038.wav,
    // so we should avoid that number
    if ( r == 38)
        r = 39;

    char f[7];
    sprintf(f, "%d.wav", r);
    return (new Common::String(*_paperShuffleSound + f));
}

Common::String *PrivateEngine::getTakeSound() {
    uint r = 1 + _rnd->getRandomNumber(4);

    char f[6];
    sprintf(f, "%d.wav", r);
    return (new Common::String(*_takeSound + f));
}

Common::String *PrivateEngine::getTakeLeaveSound() {
    uint r = _rnd->getRandomNumber(1);
    if (r == 0) {
        return (new Common::String("global/audio/mvo001.wav"));
    } else {
        return (new Common::String("global/audio/mvo006.wav"));
    }
}

Common::String *PrivateEngine::getLeaveSound() {
    uint r = 1 + _rnd->getRandomNumber(4);

    char f[6];
    sprintf(f, "%d.wav", r);
    return (new Common::String(*_leaveSound + f));
}


char *PrivateEngine::getRandomPhoneClip(char *clip, int i, int j) {
    uint r = i + _rnd->getRandomNumber(j - i);

    char *f = (char*) malloc((strlen(clip)+3)*sizeof(char));
    sprintf(f, "%s%02d", clip, r);
    return f;
}


} // End of namespace Private
