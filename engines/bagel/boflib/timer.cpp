
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

#include "common/system.h"
#include "bagel/boflib/boffo.h"
#include "bagel/boflib/debug.h"
#include "bagel/boflib/timer.h"
#include "bagel/bagel.h"

namespace Bagel {

BOOL CBofTimer::m_bModified = FALSE;
CBofTimer *CBofTimer::m_pTimerList = nullptr;

#if BOF_WINDOWS
#define GETTIME() (uint32)GetTickCount()
#elif BOF_MAC
#define GETTIME() (uint32)(16.66 * TickCount())
#endif

WindowTimer::WindowTimer(uint32 interval, UINT id, BOFCALLBACK callback) :
		_interval(interval), _id(id), _callback(callback) {
	_lastExpiryTime = g_system->getMillis();
}


CBofTimer::CBofTimer() {
	m_lLastTime = 0;
	m_nID = 0;
	m_nInterval = 0;
	m_pCallBack = nullptr;
	m_lUserInfo = 0;
	m_bActive = FALSE;

	// Another item for the list
	//
	if (m_pTimerList == nullptr) {
		m_pTimerList = this;

	} else {
		m_pTimerList->AddToTail(this);
	}

	// creating a new timer object modifies the timer list
	m_bModified = TRUE;
}


CBofTimer::CBofTimer(UINT nID, UINT nInterval, void *lUserInfo, BOFCALLBACK pCallBack) {
	m_lLastTime = 0;
	m_nID = nID;
	m_nInterval = nInterval;
	m_pCallBack = pCallBack;
	m_lUserInfo = lUserInfo;
	m_bActive = FALSE;

	// Another item for the list
	//
	if (m_pTimerList == nullptr) {
		m_pTimerList = this;

	} else {
		m_pTimerList->AddToTail(this);
	}

	// creating a new timer object modifies the timer list
	m_bModified = TRUE;
}


CBofTimer::~CBofTimer() {
	Assert(IsValidObject(this));

	if (m_pTimerList == this) {
		m_pTimerList = (CBofTimer *)m_pTimerList->GetNext();
	}

	// removing a timer object modifies the timer list
	m_bModified = TRUE;
}


VOID CBofTimer::HandleTimers() {
	CBofTimer *pTimer;
	uint32 lCurrentTime;

	pTimer = m_pTimerList;
	while (pTimer != nullptr) {
		if (pTimer->IsActive()) {
			lCurrentTime = g_system->getMillis();

			if ((UINT)(lCurrentTime - pTimer->m_lLastTime) >= pTimer->m_nInterval) {
				// Remember for next time
				pTimer->m_lLastTime = lCurrentTime;

				if (pTimer->m_pCallBack != nullptr) {
					// Execute call back
					(*pTimer->m_pCallBack)(pTimer->m_nID, pTimer->m_lUserInfo);

					// If callback modifies the timer list, then we must start over
					if (m_bModified) {
						pTimer = m_pTimerList;
						continue;
					}

					// otherwise, something is wrong
					//
				} else {
					LogWarning(BuildString("Timer without a callback: %d", pTimer->m_nID));
				}
			}
		}
		pTimer = (CBofTimer *)pTimer->GetNext();
	}
}

} // end of namespace Bagel
