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

#ifndef TETRAEDGE_GAME_CHARACTER_H
#define TETRAEDGE_GAME_CHARACTER_H

#include "common/array.h"
#include "common/str.h"
#include "common/types.h"
#include "common/ptr.h"
#include "tetraedge/te/te_animation.h"
#include "tetraedge/te/te_model_animation.h"
#include "tetraedge/te/te_vector3f32.h"
#include "tetraedge/te/te_matrix4x4.h"
#include "tetraedge/te/te_model.h"
#include "tetraedge/te/te_bezier_curve.h"
#include "tetraedge/te/te_free_move_zone.h"
#include "tetraedge/te/te_trs.h"

namespace Tetraedge {

class Character : public TeAnimation {
public:
	Character();
	virtual ~Character() {}

	struct AnimSettings {
		AnimSettings() : _stepLeft(0), _stepRight(0) {};
		Common::String _file;
		int _stepLeft;
		int _stepRight;
	};

	struct WalkSettings {
		AnimSettings _walkParts[4];

		void clear();
	};

	struct CharacterSettings {
		CharacterSettings() : _walkSpeed(0.0f) {}

		Common::String _name;
		Common::String _modelFileName;
		TeVector3f32 _defaultScale;
		Common::String _walkFileName;
		Common::HashMap<Common::String, WalkSettings> _walkSettings; // keys are "Walk", "Jog", etc
		float _walkSpeed;

		TeVector3f32 _cutSceneCurveDemiPosition;
		Common::String _defaultEyes;	// Note: Engine supports more, but in practice only one ever used.
		Common::String _defaultMouth; 	// Note: Engine supports more, but in practice only one ever used.
		Common::String _defaultBody; 	// Note: Engine supports more, but in practice only one ever used.

		void clear();
	};

	struct AnimCacheElement {
		TeIntrusivePtr<TeModelAnimation> _modelAnim;
		int _size;
	};

	enum WalkPart {
		WalkPart_Start,
		WalkPart_Loop,
		WalkPart_EndD,
		WalkPart_EndG
	};

	struct Callback {
		int x;
		Common::String s;
		int y;
		float f;
	};

	void addCallback(const Common::String &s1, const Common::String &s2, float f1, float f2);

	static void animCacheFreeAll();
	static void animCacheFreeOldest();
	static TeIntrusivePtr<TeModelAnimation> animCacheLoad(const Common::Path &path);

	float animLength(const TeModelAnimation &modelanim, long bone, long lastframe);
	float animLengthFromFile(const Common::String &animname, uint *pframeCount, uint lastframe);
	bool blendAnimation(const Common::String &animname, float amount, bool repeat, bool param_4);
	TeVector3f32 correctPosition(const TeVector3f32 &pos);
	float curveOffset();
	void deleteAllCallback();
	void deleteAnim();
	void deleteCallback(const Common::String &str1, const Common::String &str2, float f);
	//static bool deserialize(TiXmlElement *param_1, Walk *param_2);
	void endMove();

	const WalkSettings *getCurrentWalkFiles();
	bool isFramePassed(int frameno);
	bool isWalkEnd();
	int leftStepFrame(enum WalkPart walkpart);
	int rightStepFrame(enum WalkPart walkpart);
	bool loadModel(const Common::String &name, bool param_2);
	static bool loadSettings(const Common::String &path);

	bool onBonesUpdate(const Common::String &boneName, const TeMatrix4x4 &param_2);
	bool onModelAnimationFinished();
	void permanentUpdate();
	void placeOnCurve(TeIntrusivePtr<TeBezierCurve> &curve);
	//void play() // just called TeAnimation::play();
	void removeAnim();
	void removeFromCurve();
	static Common::String rootBone() { return "Pere"; }

	bool setAnimation(const Common::String &name, bool repeat, bool param_3, bool param_4, int startFrame, int endFrame);
	void setAnimationSound(const Common::String &name, uint offset);
	void setCurveOffset(float offset);
	void setFreeMoveZone(TeFreeMoveZone *zone);
	bool setShadowVisible(bool visible);
	void setStepSound(const Common::String &stepSound1, const Common::String &stepSound2);
	float speedFromAnim(double movepercent);
	//void stop(); // just maps to TeAnimation::stop();
	float translationFromAnim(const TeModelAnimation &anim, long bone, long frame);
	TeVector3f32 translationVectorFromAnim(const TeModelAnimation &anim, long bone, long frame);
	TeTRS trsFromAnim(const TeModelAnimation &anim, long bone, long frame);
	void update(double percentval);
	void updateAnimFrame();
	void updatePosition(float curveOffset);
	Common::String walkAnim(WalkPart part);
	void walkMode(const Common::String &mode);
	void walkTo(float param_1, bool param_2);

	TeIntrusivePtr<TeModel> _model;
	TeIntrusivePtr<TeModel> _shadowModel[2];
	TeSignal1Param<const Common::String &> _characterAnimPlayerFinishedSignal;
	TeSignal1Param<const Common::String &> _onCharacterAnimFinishedSignal;

	const CharacterSettings &characterSettings() const { return _characterSettings; }
	const Common::String walkModeStr() const { return _walkModeStr; }
	const Common::String curAnimName() const { return _curAnimName; }
	bool needsSomeUpdate() const { return _needsSomeUpdate; }
	void setCharLookingAt(Character *other) { _charLookingAt = other; }

private:
	float _curveOffset;
	TeIntrusivePtr<TeBezierCurve> _curve;
	TeFreeMoveZone *_freeMoveZone;
	Common::String _stepSound1;
	Common::String _stepSound2;
	Common::String _walkModeStr; // Walk or Jog
	Common::String _animSound;

	Character *_charLookingAt;

	uint _animSoundOffset;

	TeIntrusivePtr<TeModelAnimation> _curModelAnim;

	CharacterSettings _characterSettings;

	int _walkPart0AnimLen;
	int _walkPart1AnimLen;
	int _walkPart3AnimLen;

	uint32 _walkPart0AnimFrameCount;
	uint32 _walkPart1AnimFrameCount;
	uint32 _walkPart3AnimFrameCount;

	int _lastFrame;
	int _lastAnimFrame;
	bool _missingCurrentAnim;
	bool _someRepeatFlag; // TODO: what is this?
	bool _callbacksChanged;
	bool _needsSomeUpdate; // TODO: what is this? Field 0x85.

	// TODO: work out how these are different
	Common::String _setAnimName;
	Common::String _curAnimName;

	Common::HashMap<Common::String, Common::Array<Callback *>> _callbacks;

	static Common::Array<AnimCacheElement> _animCache;
	static uint _animCacheSize;
	static Common::HashMap<Common::String, CharacterSettings> *_globalCharacterSettings;

};

} // end namespace Tetraedge

#endif // TETRAEDGE_GAME_CHARACTER_H
