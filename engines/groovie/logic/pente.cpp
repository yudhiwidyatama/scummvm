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

#include "groovie/logic/pente.h"
#include "common/stack.h"
#include "common/algorithm.h"
#include "groovie/groovie.h"

namespace Groovie {

#ifdef UINT_MAX
#undef UINT_MAX
#endif
const uint UINT_MAX = (uint)-1;
const uint WIN_SCORE = 100000000;
const uint CAPTURE_SCORE = 1000000;

struct pentePlayerTable {
	Common::FixedStack<int, 813> lines;
};

struct penteTable {
	pentePlayerTable player;
	pentePlayerTable stauf;
	uint playerScore;
	uint staufScore;
	byte playerLines;
	byte staufLines;
	byte width;
	byte height;
	uint16 boardSize;
	byte lineLength;
	uint16 moveCounter;
	byte boardState[20][15];
	uint16 linesCounter;
	uint16 linesTable[20][15][21];
	byte numAdjacentPieces[20][15];
	byte calcTouchingPieces; // the deepest level of AI recursion sets this to 0, and then sets it back to 1 when returning
};

void PenteGame::addLine(int x, int y, int linesCounter) {
	int i = ++_table->linesTable[x][y][0];
	_table->linesTable[x][y][i] = linesCounter;
}

void PenteGame::buildLookupTable() {
	int width = _table->width;
	int height = _table->height;
	uint16 linesCounter = 0;
	int lineLength = _table->lineLength;

	// slope of (1,0)
	for (int x = 0; x <= width - lineLength; x++) {
		for (int y = 0; y < height; y++) {
			for (int z = 0; z < lineLength; z++) {
				addLine(x + z, y, linesCounter);
			}
			linesCounter++;
		}
	}

	// slope of (0,1)
	for (int x = 0; x < width; x++) {
		for (int y = 0; y <= height - lineLength; y++) {
			for (int z = 0; z < lineLength; z++) {
				addLine(x, y + z, linesCounter);
			}
			linesCounter++;
		}
	}

	// slope of (1,1)
	for (int x = 0; x <= width - lineLength; x++) {
		for (int y = 0; y <= height - lineLength; y++) {
			for (int z = 0; z < lineLength; z++) {
				addLine(x + z, y + z, linesCounter);
			}
			linesCounter++;
		}
	}

	// slope of (1,-1)
	for (int x = 0; x <= width - lineLength; x++) {
		for (int y = lineLength - 1; y < height; y++) {
			for (int z = 0; z < lineLength; z++) {
				addLine(x + z, y - z, linesCounter);
			}
			linesCounter++;
		}
	}

	_table->linesCounter = linesCounter;
}

void PenteGame::penteDeInit() {
	delete _table;
	_table = NULL;
}

void PenteGame::penteInit(uint width, uint height, uint length) {
	_table = new penteTable();
	_table->width = width;
	_table->height = height;
	_table->boardSize = height * width;
	_table->lineLength = length;
	memset(_table->boardState, 0, sizeof(_table->boardState));

	buildLookupTable();
	assert(_table->linesCounter == 812);

	_table->staufScore = (uint)_table->linesCounter;
	_table->playerScore = (uint)_table->linesCounter;
	memset(_table->numAdjacentPieces, 0, sizeof(_table->numAdjacentPieces));

	_table->calcTouchingPieces = 1;
}

uint &PenteGame::getPlayerTable(bool staufTurn, pentePlayerTable *&pt) {
	pt = staufTurn ? &_table->stauf : &_table->player;
	return staufTurn ? _table->staufScore : _table->playerScore;
}

void PenteGame::scoreLine(uint16 lineIndex, bool stauf_turn, bool revert) {
	pentePlayerTable *playerTable;
	uint &score = getPlayerTable(stauf_turn, playerTable);

	int lineLength, mult;
	if (revert) {
		lineLength = --playerTable->lines[lineIndex];
		mult = -1;
	} else {
		lineLength = playerTable->lines[lineIndex]++;
		mult = 1;
	}

	if (_table->lineLength - lineLength == 1) {
		score = (int)score + (int)WIN_SCORE * mult;
	} else {
		pentePlayerTable *opponentTable;
		uint &opponentScore = getPlayerTable(!stauf_turn, opponentTable);
		int opponentLineLength = opponentTable->lines[lineIndex];
		if (lineLength == 0) {
			opponentScore += (-(1 << ((byte)opponentLineLength & 0x1f))) * mult;
			if (_table->lineLength - opponentLineLength == 1) {
				if (stauf_turn)
					_table->playerLines -= mult;
				else
					_table->staufLines -= mult;
			}
		}
		if (opponentLineLength == 0) {
			score += (1 << ((byte)lineLength & 0x1f)) * mult;
			if (_table->lineLength - lineLength == 2) {
				byte b;
				if (stauf_turn)
					b = (_table->staufLines += mult);
				else
					b = (_table->playerLines += mult);

				if (revert)
					b -= mult;

				if (1 < b) {
					score = (int)score + (int)CAPTURE_SCORE * mult;
				}
			}
		}
	}
}

void PenteGame::calcTouchingPieces(byte moveX, byte moveY, bool revert) {
	byte endX, endY;

	if (moveX + 1 < _table->width) {
		endX = moveX + 1;
	} else {
		endX = _table->width - 1;
	}

	if (moveY + 1 < _table->height) {
		endY = moveY + 1;
	} else {
		endY = _table->height - 1;
	}

	byte x = 0;
	if (1 < moveX) {
		x = moveX - 1;
	}

	for (; x <= endX; x++) {
		byte y = 0;
		if (1 < moveY) {
			y = moveY - 1;
		}

		for (; y <= endY; y++) {
			if (revert)
				_table->numAdjacentPieces[x][y]--;
			else
				_table->numAdjacentPieces[x][y]++;
		}
	}
}

void PenteGame::updateScore(byte move_y, byte move_x, bool stauf_turn) {
	_table->boardState[move_x][move_y] = stauf_turn ? 88 : 79;
	uint16 lines = _table->linesTable[move_x][move_y][0];

	for (int i = 1; i <= lines; i++) {
		uint16 lineIndex = _table->linesTable[move_x][move_y][i];
		scoreLine(lineIndex, stauf_turn, false);
	}

	if (_table->calcTouchingPieces != 0) {
		calcTouchingPieces(move_x, move_y, false);
	}

	_table->moveCounter++;
}

void PenteGame::revertScore(byte y, byte x) {
	bool stauf_turn = _table->boardState[x][y] == 88;
	_table->boardState[x][y] = 0;
	_table->moveCounter--;
	uint lines = _table->linesTable[x][y][0];

	for (uint i = 1; i <= lines; i++) {
		uint16 lineIndex = _table->linesTable[x][y][i];
		scoreLine(lineIndex, stauf_turn, true);
	}

	if (_table->calcTouchingPieces != 0) {
		calcTouchingPieces(x, y, true);
	}
}

byte PenteGame::scoreCaptureSingle(byte x, byte y, int slopeX, int slopeY) {
	byte x1 = x + slopeX;
	byte y1 = y + slopeY;
	byte x2 = x + slopeX * 2;
	byte y2 = y + slopeY * 2;
	byte endX = x + slopeX * 3;
	byte endY = y + slopeY * 3;

	// we don't need to check for below 0 when we have unsigned types
	if (x >= _table->width || y >= _table->height)
		return 0;
	if (endX >= _table->width || endY >= _table->height)
		return 0;

	auto &boardState = _table->boardState;
	byte captor = boardState[x][y];
	byte captive = captor == 88 ? 79 : 88;

	// make sure the captor is at the start and end of the line
	if (boardState[endX][endY] != captor)
		return 0;

	// check that the captive is both of the middle pieces
	if (boardState[x1][y1] != captive || boardState[x2][y2] != captive)
		return 0;

	revertScore(y1, x1);
	revertScore(y2, x2);
	return 1;
}

struct Slope {
	int x, y;
};
// the order of these is important because we return the bitMask
Slope slopes[] = {{1, 0},
				  {1, 1},
				  {0, 1},
				  {-1, 1},
				  {-1, 0},
				  {-1, -1},
				  {0, -1},
				  {1, -1}};

uint PenteGame::scoreCapture(byte y, byte x) {
	byte bitMask = 0;
	bool isStauf = _table->boardState[x][y] == 88;

	for (const Slope &slope : slopes) {
		bitMask <<= 1;
		bitMask |= scoreCaptureSingle(x, y, slope.x, slope.y);
	}

	for (int i = bitMask; i; i >>= 1) {
		if ((i & 1) == 0)
			continue;
		pentePlayerTable *playerTable;
		uint &score = getPlayerTable(isStauf, playerTable);

		int lineLength = ++playerTable->lines[_table->linesCounter];
		if (_table->lineLength == lineLength) {
			score += WIN_SCORE;
		} else {
			score += 1 << ((lineLength - 1U) & 0x1f);
		}
	}
	return bitMask;
}

void PenteGame::animateCapture(short move, byte *bitMaskG, short *param_3, short *param_4) {
	byte x;
	byte y;

	x = (byte)((int)move / 0xf);
	y = 0xe - (char)((int)move % 0xf);

	byte &bitMask = *bitMaskG;
	byte bVar3 = 0;
	for (bVar3 = 0; bVar3 < 8; bVar3++) {
		if (bitMask >> bVar3 & 1) {
			bitMask = '\x01' << (bVar3 & 0x1f) ^ bitMask;
			break;
		}
	}

	short sVar4;
	switch (bVar3) {
	case 0:
		*param_3 = (x + 2) * 0xf - (uint16)y;
		*param_4 = ((uint16)x * 0xf - (uint16)y) + 0x2e;
		return;
	case 1:
		*param_3 = (x + 1) * 0xf - (uint16)y;
		*param_4 = ((uint16)x * 0xf - (uint16)y) + 0x10;
		return;
	case 2:
		sVar4 = (uint16)x * 0xf - (uint16)y;
		*param_3 = sVar4;
		*param_4 = sVar4 + -0xe;
		return;
	case 3:
		sVar4 = (uint16)x * 0xf - (uint16)y;
		*param_3 = sVar4 + -1;
		*param_4 = sVar4 + -0x10;
		return;
	case 4:
		sVar4 = (uint16)x * 0xf - (uint16)y;
		*param_3 = sVar4 + -2;
		*param_4 = sVar4 + -0x12;
		return;
	case 5:
		sVar4 = (uint16)x * 0xf - (uint16)y;
		*param_3 = sVar4 + 0xd;
		*param_4 = sVar4 + 0xc;
		return;
	case 6:
		sVar4 = (uint16)x * 0xf - (uint16)y;
		*param_3 = sVar4 + 0x1c;
		*param_4 = sVar4 + 0x2a;
		return;
	case 7:
		sVar4 = (uint16)x * 0xf - (uint16)y;
		*param_3 = sVar4 + 0x1d;
		*param_4 = sVar4 + 0x2c;
	}
	return;
}

void PenteGame::revertCapture(byte y, byte x, byte bitMask) {
	bool isPlayer = _table->boardState[x][y] == 79;
	for (int i = bitMask; i; i >>= 1) {
		if ((i & 1) == 0)
			continue;

		pentePlayerTable *playerTable;
		uint &score = getPlayerTable(!isPlayer, playerTable);

		int linesCounter = --playerTable->lines[_table->linesCounter];

		if (_table->lineLength - linesCounter == 1) {
			score -= WIN_SCORE;
		} else {
			score -= (1 << ((char)linesCounter & 0x1f));
		}
	}

	for (int i = 0; i < 8; i++) {
		if ((bitMask >> i & 1) == 0)
			continue;

		Slope &slope = slopes[7 - i];
		updateScore(y + slope.y * 2, x + slope.x * 2, isPlayer);
		updateScore(y + slope.y, x + slope.x, isPlayer);
	}
}

int PenteGame::scoreMoveAndRevert(byte x, byte y, char depth, int parentScore, bool &gameOver) {
	updateScore(y, x, _table->moveCounter % 2);
	uint score = scoreCapture(y, x);

	if (_table->playerScore >= WIN_SCORE || _table->staufScore >= WIN_SCORE)
		gameOver = true;
	else
		gameOver = false;

	int scoreDiff;
	if (depth > 0 && gameOver==false && _table->boardSize != _table->moveCounter) {
		scoreDiff = aiRecurse(depth, parentScore);
	} else {
		if (_table->moveCounter % 2 == 0) {
			scoreDiff = _table->playerScore - _table->staufScore;
		} else {
			scoreDiff = _table->staufScore - _table->playerScore;
		}
	}
	if (score != 0) {
		revertCapture(y, x, score);
	}
	revertScore(y, x);
	return scoreDiff;
}

int PenteGame::scoreMoveAndRevert(byte x, byte y, char depth, int parentScore) {
	// same thing, but don't need to provide the reference to the gameOverBool
	bool gameOver;
	return scoreMoveAndRevert(x, y, depth, parentScore, gameOver);
}

int PenteGame::aiRecurseTail(int parentScore) {
	int best_score = 0x7fffffff;

	_table->calcTouchingPieces = 0;
	for (byte x = 0; x < _table->width; x++) {
		for (byte y = 0; y < _table->height; y++) {
			if ((_table->boardState[x][y] != 0) ||
				(_table->numAdjacentPieces[x][y] == 0)) {
				continue;
			}

			int scoreDiff = scoreMoveAndRevert(x, y, 0, 0);
			if (scoreDiff < best_score) {
				best_score = scoreDiff;
			}
			if (-parentScore != best_score && parentScore <= -best_score) {
				_table->calcTouchingPieces = 1;
				return -best_score;
			}
		}
	}
	_table->calcTouchingPieces = 1;

	return -best_score;
}

int PenteGame::aiRecurse(char depth, int parent_score) {
	if (depth == 1) {
		// don't do more recursion
		return aiRecurseTail(parent_score);
	}

	// do more recursion after finding some good moves
	struct GoodMove {
		int scoreDiff;
		byte x, y;

		bool operator()(GoodMove a, GoodMove b) {
			return a.scoreDiff < b.scoreDiff;
		}
	};
	Common::FixedStack<GoodMove, 300> goodMoves; // 300 slots because the board is 20x15, but we rarely need many since the search excludes spots with no adjacenet pieces
	int best_score = 0x7fffffff;

	for (byte x = 0; x < _table->width; x++) {
		for (byte y = 0; y < _table->height; y++) {
			if ((_table->boardState[x][y] != 0) ||
				(_table->numAdjacentPieces[x][y] == 0)) {
				continue;
			}

			int scoreDiff = scoreMoveAndRevert(x, y, 0, 0);
			goodMoves.push({scoreDiff, x, y});
		}
	}

	// sort ascending by scoreDiff, most of the time you'll see scores like -40 at the top and -34 at the end
	Common::sort(&goodMoves[0], &goodMoves.top(), goodMoves[0]);

	for (uint i = 0; i < goodMoves.size(); i++) {
		byte x = goodMoves[i].x;
		byte y = goodMoves[i].y;

		int scoreDiff = scoreMoveAndRevert(x, y, depth - 1, best_score);
		if (scoreDiff < best_score) {
			best_score = scoreDiff;
		}
		if (-parent_score != best_score && parent_score <= -best_score)
			break;
	}
	return -best_score;
}

uint16 PenteGame::aiGetBestMove(uint param_1, int param_2, int param_3, byte depth) {
	for (int x = 0; x < _table->width; x++) {
		for (int y = 0; y < _table->height; y++) {
			if (_table->boardState[x][y] != 0 || _table->numAdjacentPieces[x][y] == 0)
				continue;

			bool gameOver;
			scoreMoveAndRevert(x, y, 0, 0, gameOver);
			if (gameOver) {
				return y + x * 100;
			}
		}
	}

	byte counter = 1;
	int bestScore = 0x7fffffff;
	uint16 bestMove = 0xffff;

	for (; bestScore > 99999999 && depth > 1; depth--) {
		for (int x = 0; x < _table->width; x++) {
			for (int y = 0; y < _table->height; y++) {
				if (_table->boardState[x][y] != 0 || _table->numAdjacentPieces[x][y] == 0)
					continue;

				int scoreRecurse = scoreMoveAndRevert(x, y, depth - 1, bestScore);

				if (scoreRecurse < bestScore) {
					counter = 1;
					bestMove = x * 100 + y;
					bestScore = scoreRecurse;
				} else {
					if (scoreRecurse == bestScore) {
						counter += 1;
						uint rng = _random.getRandomNumber(UINT_MAX);
						if ((rng % CAPTURE_SCORE) * counter < CAPTURE_SCORE) {
							bestMove = x * 100 + y;
						}
					}
				}
			}
		}
	}
	return bestMove;
}

int varsMoveToXY(byte var0, byte var1, byte var2, byte &x, byte &y) {
	int move = ((char)var0 * 10 + (short)(char)var1) * 10 + (short)(char)var2;
	x = (byte)(move / 15);
	y = 0xe - (char)((int)move % 15);
	return move;
}

void aiMoveToXY(int move, byte &x, byte &y) {
	x = move / 100;
	y = move % 100;
}

void moveToVars(int move, byte &var0, byte &var1, byte &var2) {
	var0 = (byte)(move / 100);
	var1 = (byte)((move % 100) / 10);
	var2 = (byte)(move % 10);
}

void moveXYToVars(uint x, uint y, byte &var0, byte &var1, byte &var2) {
	int move = (x * 0xf - y) + 0xe;
	moveToVars(move, var0, var1, var2);
}

void PenteGame::run(byte *vars) {
	uint16 uVar1;
	int iVar2;
	byte ai_depth;
	short local_2;

	byte op = vars[4];
	if (_table == NULL && op != 0) {
		penteInit(20, 15, 5);
	}
	debugC(kDebugLogic, "penteOp vars[4]: %d", (int)op);

	switch (op) {
	case 0:
		penteDeInit();
		return;
	case 1:
		_globalPlayerMove = varsMoveToXY(vars[0], vars[1], vars[2], _globalX, _globalY);
		debugC(kDebugLogic, "player moved to %d, %d", (int)_globalX, (int)_globalY);
		updateScore(_globalY, _globalX, _table->moveCounter % 2);
		_global2 = scoreCapture(_globalY, _globalX);
		return;
	case 2:
	case 4:
		if (_global2 != '\0') {
			if (_global1 < 0) {
				animateCapture(_globalPlayerMove, (byte *)&_global2, &local_2, &_global1);
				vars[5] = 1;
				moveToVars(local_2, vars[0], vars[1], vars[2]);
				return;
			}
		LAB_00412da4:
			vars[0] = (byte)((int)_global1 / 100);
			vars[1] = (byte)((int)(_global1 % 100) / 10);
			iVar2 = (int)_global1;
			vars[2] = (byte)(iVar2 % 10);
			_global1 = -1;
			vars[5] = 1;
			return;
		}
		if (-1 < _global1)
			goto LAB_00412da4;
		if (_table->playerScore < WIN_SCORE) {
			if ((_table->staufScore < WIN_SCORE) &&
				(uVar1 = _table->moveCounter)) {
				vars[5] = 0;
				return;
			}
			if (_table->playerScore < WIN_SCORE) {
				vars[5] = 2; // Stauf wins
				if (_table->staufScore < WIN_SCORE) {
					vars[5] = 4; // player wins because the board is full?
				}
				goto DEALLOC;
			}
		}
		vars[5] = 3; // player wins
	DEALLOC:
		penteDeInit();
		return;
	case 3:
		break;
	case 5:
		// asking Samantha to make a move? this does a bunch of queries to check if pieces belong to stauf or the player?
		byte x, y;
		varsMoveToXY(vars[0], vars[1], vars[2], x, y);
		ai_depth = _table->boardState[x][y];
		if (ai_depth == 0) {
			vars[3] = 0;
			return;
		}
		if (ai_depth == 0x4f) {
			vars[3] = 2;
			return;
		}
		if (ai_depth != 0x58) {
			return;
		}
		vars[3] = 1;
	default:
		return;
	}
	ai_depth = vars[6];
	if (ai_depth == 0) {
		ai_depth = 3;
	} else {
		if (ai_depth == 1) {
			ai_depth = 4;
		} else {
			if (ai_depth != 2)
				goto LAB_00412e85;
			ai_depth = 5;
		}
	}
	_globalPlayerMove = aiGetBestMove(0, 0, 0, ai_depth);
LAB_00412e85:
	aiMoveToXY(_globalPlayerMove, _globalX, _globalY);
	debugC(kDebugLogic, "Stauf moved to %d, %d", (int)_globalX, (int)_globalY);
	updateScore(_globalY, _globalX, _table->moveCounter % 2);
	_global2 = scoreCapture(_globalY, _globalX);
	_globalPlayerMove = ((uint16)_globalX * 0xf - (uint16)_globalY) + 0xe;
	moveXYToVars(_globalX, _globalY, vars[0], vars[1], vars[2]);
}

PenteGame::PenteGame() : _random("PenteGame") {
	_table = NULL;
	_global1 = -1;
	_globalY = 0;
	_globalX = 0;
	_global2 = 0;
	_globalPlayerMove = 0;
#if 0
	test();
#endif
}

void PenteGame::test() {
	warning("starting PenteGame::test()");
	uint32 oldSeed = _random.getSeed();

	// 6 moves per line
	testGame(3,
		{
			/*x=*/10, /*y=*/6, /*x=*/9, /*y=*/6, /*x=*/10, /*y=*/7, /*x=*/10, /*y=*/5, /*x=*/10, /*y=*/8, /*x=*/9, /*y=*/9,
			/*x=*/10, /*y=*/9, /*x=*/10, /*y=*/10, /*x=*/9, /*y=*/8, /*x=*/8, /*y=*/7, /*x=*/8, /*y=*/8, /*x=*/7, /*y=*/8,
			/*x=*/6, /*y=*/9, /*x=*/11, /*y=*/4,
		}, false);

	testGame(10,
		{
			/*x=*/10, /*y=*/6, /*x=*/11, /*y=*/7, /*x=*/10, /*y=*/5, /*x=*/10, /*y=*/7, /*x=*/9, /*y=*/7, /*x=*/12, /*y=*/7,
			/*x=*/10, /*y=*/4, /*x=*/8, /*y=*/8, /*x=*/10, /*y=*/3, /*x=*/11, /*y=*/5, /*x=*/10, /*y=*/2, /*x=*/9, /*y=*/7,
			/*x=*/10, /*y=*/6,
		}, true);

	// test bottom left corner
	testGame(1993,
		{
			/*x=*/0, /*y=*/0, /*x=*/1, /*y=*/1, /*x=*/1, /*y=*/0, /*x=*/2, /*y=*/0, /*x=*/0, /*y=*/1, /*x=*/0, /*y=*/2,
			/*x=*/2, /*y=*/1, /*x=*/3, /*y=*/2, /*x=*/1, /*y=*/2, /*x=*/2, /*y=*/3, /*x=*/4, /*y=*/1, /*x=*/1, /*y=*/4,
			/*x=*/5, /*y=*/1, /*x=*/6, /*y=*/1, /*x=*/3, /*y=*/0, /*x=*/5, /*y=*/2, /*x=*/4, /*y=*/3, /*x=*/3, /*y=*/1,
			/*x=*/3, /*y=*/3, /*x=*/5, /*y=*/3, /*x=*/4, /*y=*/1, /*x=*/4, /*y=*/3, /*x=*/3, /*y=*/3, /*x=*/3, /*y=*/4,
			/*x=*/2, /*y=*/5, /*x=*/7, /*y=*/0
		}, false);

	// test bottom right corner
	testGame(1995,
		{
			/*x=*/19, /*y=*/0, /*x=*/18, /*y=*/1, /*x=*/19, /*y=*/1, /*x=*/18, /*y=*/2, /*x=*/18, /*y=*/0, /*x=*/18, /*y=*/3,
			/*x=*/18, /*y=*/4, /*x=*/17, /*y=*/5, /*x=*/17, /*y=*/0, /*x=*/16, /*y=*/5, /*x=*/17, /*y=*/4, /*x=*/16, /*y=*/4,
			/*x=*/18, /*y=*/5, /*x=*/18, /*y=*/6, /*x=*/18, /*y=*/5, /*x=*/15, /*y=*/3, /*x=*/18, /*y=*/4, /*x=*/14, /*y=*/2,
		}, false);

	// test top left corner
	testGame(1996,
		{
			/*x=*/0, /*y=*/14, /*x=*/1, /*y=*/13, /*x=*/1, /*y=*/14, /*x=*/2, /*y=*/14, /*x=*/0, /*y=*/13, /*x=*/0, /*y=*/12,
			/*x=*/1, /*y=*/12, /*x=*/2, /*y=*/11, /*x=*/2, /*y=*/12, /*x=*/3, /*y=*/12, /*x=*/4, /*y=*/13, /*x=*/1, /*y=*/10,
			/*x=*/0, /*y=*/9, /*x=*/3, /*y=*/10, /*x=*/1, /*y=*/12, /*x=*/4, /*y=*/9, /*x=*/5, /*y=*/8, /*x=*/6, /*y=*/9,
			/*x=*/3, /*y=*/11, /*x=*/6, /*y=*/10, /*x=*/6, /*y=*/11, /*x=*/4, /*y=*/8, /*x=*/3, /*y=*/9, /*x=*/4, /*y=*/10,
			/*x=*/4, /*y=*/11, /*x=*/2, /*y=*/10, /*x=*/0, /*y=*/10, /*x=*/5, /*y=*/10
		}, false);

	// test top right corner
	testGame(2019,
		{
			/*x=*/19, /*y=*/14, /*x=*/18, /*y=*/13, /*x=*/19, /*y=*/12, /*x=*/18, /*y=*/12, /*x=*/18, /*y=*/11, /*x=*/17, /*y=*/10,
			/*x=*/18, /*y=*/14, /*x=*/16, /*y=*/11, /*x=*/18, /*y=*/9, /*x=*/15, /*y=*/12, /*x=*/14, /*y=*/13, /*x=*/15, /*y=*/10,
			/*x=*/15, /*y=*/11, /*x=*/14, /*y=*/10, /*x=*/17, /*y=*/12, /*x=*/16, /*y=*/10, /*x=*/13, /*y=*/10, /*x=*/18, /*y=*/10
		}, false);

	_random.setSeed(oldSeed);
	warning("finished PenteGame::test()");
}

void PenteGame::testGame(uint32 seed, Common::Array<int> moves, bool playerWin) {
	byte vars[1024];
	byte &winner = vars[5];
	byte &op = vars[4];

	warning("starting PenteGame::testGame(%u, %u, %d)", seed, moves.size(), (int)playerWin);
	memset(vars, 0, sizeof(vars));
	_random.setSeed(seed);

	op = 0;
	run(vars);

	for (uint i = 0; i < moves.size(); i += 2) {
		if (winner)
			error("%u: early winner: %d", i, (int)winner);

		int x = moves[i];
		int y = moves[i + 1];

		if (i % 4) {
			// check Stauf's move
			op = 3;
			run(vars);

			byte sX, sY;
			varsMoveToXY(vars[0], vars[1], vars[2], sX, sY);

			if (sX != x || sY != y)
				error("%u: Stauf, expected (%d, %d), got (%d, %d)", i, (int)x, (int)y, (int)sX, (int)sY);

			do {
				op = 4;
				run(vars);
			} while (winner == 1);
			continue;
		}

		moveXYToVars(x, y, vars[0], vars[1], vars[2]);
		op = 1;
		run(vars);

		do {
			op = 2;
			run(vars);
		} while (winner == 1);
	}

	if (playerWin && winner != 3)
		error("player didn't win, winner: %d", (int)winner);
	else if (playerWin == false && winner != 2)
		error("Stauf didn't win, winner: %d", (int)winner);

	warning("finished PenteGame::testGame(%u, %u, %d)", seed, moves.size(), (int)playerWin);
}

} // namespace Groovie
