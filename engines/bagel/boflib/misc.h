
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

#ifndef BAGEL_BOFLIB_MISC_H
#define BAGEL_BOFLIB_MISC_H

#include "bagel/boflib/boffo.h"
#include "bagel/boflib/stdinc.h"
#include "bagel/boflib/error.h"
#include "bagel/boflib/date_functions.h"
#include "bagel/boflib/file_functions.h"
#include "bagel/boflib/string_functions.h"

namespace Bagel {

/**
 * Log an error message
*/
extern VOID ErrorLog(const CHAR *format, ...);
inline VOID SetErrLogFile(const CHAR *pszFileName) {}

extern INT MapWindowsPointSize(INT pointSize);

/**
 * Return a true / false based on the probability given
 * @param nProbability      The probability of returning a true
 * @return                  A TRUE <nProbability> of the tine
 */
extern BOOL ProbableTrue(INT);

/**
 * Starts a Millisecond timer
 */
extern VOID TimerStart();

/**
 * Stops the timer started by TimerStart, returns time elapsed.
 * @return      Number of MilliSeconds elapsed since call to TimerStart
 */
extern DWORD TimerStop();

/**
 * Returns the current elapsed time in milliseconds
*/
extern DWORD GetTimer();

/**
 * Pauses the computer for specified number of MilliSeconds
 * @param milli     Number of milliseconds
 */
extern VOID Sleep(DWORD milli);

extern Fixed FixedDivide(Fixed Dividend, Fixed Divisor);
extern Fixed FixedMultiply(Fixed Multiplicand, Fixed Multiplier);

#define IntToFixed(i) (Fixed)(((long)(i)) << 16)
#define FixedToInt(f) (int)(((long)f) >> 16)

//////////////////////////////////////////////////////////////////////////////
//
// Memory allocation routines (Should be put into their own MEMORY module)
//
//////////////////////////////////////////////////////////////////////////////


/**
 * Allocates a memory block of specified size
 * @param nSize         Number of bytes to allocate
 * @param pFile         Source file name
 * @param nLine         Source file line number
 * @param bClear        true if buffer should be cleared
 * @return              Pointer to new buffer
 */
extern void *BofMemAlloc(uint32 nSize, const char *pFile, int nLine, bool bClear);

/**
 * Re-Allocates a memory block to the specified size
 * @param pOldPointer   Old memory pointer
 * @param nNewSize      New buffer size
 * @param pFile         Source file name
 * @param nLine         Source file line number
 * @return              Pointer to new buffer
 */
extern void *BofMemReAlloc(void *pOldPtr, uint32 nNewSize, const char *pFile, int nLine);

/**
 * Frees specified memory block
 * @param pBuf          Buffer to de-allocate
 * @param pFile         Source file name
 * @param nLine         Source file line number
 **/
extern void BofMemFree(void *pBuf, const char *pszFile, int nLine);

#define BofAlloc(n) BofMemAlloc((n), __FILE__, __LINE__, FALSE)
#define BofCAlloc(n, m) BofMemAlloc((uint32)(n) * (m), __FILE__, __LINE__, TRUE)
#define BofReAlloc(p, n) BofMemReAlloc((p), (n), __FILE__, __LINE__)
#define BofFree(p) BofMemFree((p), __FILE__, __LINE__)

#define BofMemSet memset
#define BofMemCopy memcpy
#define BofMemMove memmove

inline uint32 GetFreePhysMem() {
	return 999999;
}
inline uint32 GetFreeMem() {
	return 999999;
}

/**
 * Writes specified setting to specified .INI file
 * @param pszFileName       Name of .INI file to write to
 * @param pszSection        Storage section in .INI for option
 * @param pszVar            Option to insert/update
 * @param pszNewValue       New Value for this option
 * @return                  Error return code
 */
extern ERROR_CODE WriteIniSetting(const CHAR *, const CHAR *, const CHAR *, const CHAR *);

/**
 * Reads specified setting from specified .INI file
 *
 * @param pszFile       Name of .INI file to read from
 * @param pszSection    Storage section in .INI for option
 * @param pszVar        Option to read
 * @param pszValue      Buffer to hold answer
 * @param pszDefault    Default answer if option not exist
 * @param nMaxLen       Max buffer length for answer
 * @return              Error return code
 */
extern ERROR_CODE ReadIniSetting(const CHAR *, const CHAR *, const CHAR *, CHAR *, const CHAR *, UINT);

/**
 * Writes specified setting to specified .INI file
 * @param pszFileName   Name of .INI file to write to
 * @param pszSection    Storage section in .INI for option
 * @param pszVar        Option to insert/update
 * @param nNewValue     New Value for this option
 * @return              Error return code
 */
extern ERROR_CODE WriteIniSetting(const CHAR *, const CHAR *, const CHAR *, INT);

/**
 * Reads specified setting from specified .INI file
 * @param pszFile       Name of .INI file to read from
 * @param pszSection    Storage section in .INI for option
 * @param pszVar        Option to read
 * @param pValue        Buffer to hold answer
 * @param nDefault      Default answer if option not exist
 * @return              Error return code
 */
extern ERROR_CODE ReadIniSetting(const CHAR *, const CHAR *, const CHAR *, INT *, INT);

/**
 * Encrypts specified buffer
 * @param pBuf          Buffer to encrypt
 * @param lSize         Number of bytes in buffer
 * @param pszPassword   Optional password to encrypt with
 */
VOID Encrypt(VOID *, LONG, const CHAR *pPassword = nullptr);
#define Decrypt Encrypt

extern VOID EncryptPartial(VOID *, LONG, LONG, const CHAR *pPassword = nullptr);
#define DecryptPartial EncryptPartial

#ifndef ABS
#define ABS(x) ((x) > 0 ? (x) : -(x))
#endif

extern BOOL IsKeyDown(uint32 lKeyCode);

// Debugging
extern void LIVEDEBUGGING(CHAR *pMessage1, CHAR *pMessage2);

// Globals
extern BOOL gLiveDebugging;

} // namespace Bagel

#endif
