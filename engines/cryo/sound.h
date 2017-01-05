#pragma once

#include "audio/audiostream.h"
#include "audio/mixer.h"
#include "audio/decoders/raw.h"

#include "cryo/cryolib.h"

namespace Cryo {

class CryoEngine;

class CSoundChannel {
private:
	Audio::Mixer *_mixer;
	Audio::QueuingAudioStream *_audioStream;
	Audio::SoundHandle _soundHandle;
	unsigned int _sampleRate;
	bool _stereo;

	void applyVolumeChange();

public:
	CSoundChannel(Audio::Mixer *mixer, unsigned int sampleRate, bool stereo);
	~CSoundChannel();

	// Queue a new buffer, cancel any previously queued buffers if playNow is set
	void queueBuffer(byte *buffer, unsigned int size, bool playNow = false);

	// Stop playing and purge play queue
	void stop();

	// How many buffers in queue (including currently playing one)
	unsigned int numQueued();

	// Volume control
	int _volumeLeft, _volumeRight;
	unsigned int getVolume();
	void setVolume(unsigned int volumeLeft, unsigned int volumeRight);
	void setVolumeLeft(unsigned int volume);
	void setVolumeRight(unsigned int volume);
};

#define kCryoMaxClSounds 64

class SoundGroup {
private:
	CryoEngine *_vm;

	Sound *_sounds[kCryoMaxClSounds];
	int16 _numSounds;
	int16 _soundIndex;
	int16 _playIndex;

public:
	SoundGroup(CryoEngine *vm, int16 numSounds, int16 length, int16 sampleSize, float rate, int16 mode);
	~SoundGroup();

	bool assignDatas(void *buffer, int length, bool isSigned);
	void playNextSample(SoundChannel *ch);
	bool setDatas(void *data, int length, bool isSigned);
	void *getNextBuffer();
};

}
