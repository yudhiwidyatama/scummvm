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

#include "bagel/spacebar/filter.h"
#include "bagel/spacebar/main_window.h"
#include "bagel/spacebar/master_win.h"
#include "bagel/boflib/gfx/palette.h"
#include "bagel/boflib/string.h"
#include "bagel/boflib/gfx/text.h"
#include "bagel/baglib/bagel.h"
#include "bagel/boflib/misc.h"
#include "bagel/boflib/sound.h"

namespace Bagel {
namespace SpaceBar {

//
// Preprocessor definitions.
//
#define TRIFILTERBMP "$SBARDIR\\TRISECKS\\OBJ\\SUNGLASS.BMP"
#define VILDROIDTIPFILE "$SBARDIR\\VILDROID\\TIP.TXT"
#define VILDROIDADDFILE "$SBARDIR\\VILDROID\\ADD.TXT"
#define VILDROIDGRAFITTI "$SBARDIR\\VILDROID\\OBJ\\DANG.BMP"
#define VILDROIDSTATSTEXTSIZE 18
#define VILDROIDTIPSTEXTSIZE 18
#define VILDROIDCHIPTEXTWIDTH 480
#define VILDROIDTIPSCROLLSPEED  5
#define GREENCHIPFILE "$SBARDIR\\VILDROID\\GCHIP.TXT"
#define BLUECHIPFILE "$SBARDIR\\VILDROID\\BUCHIP.TXT"
#define BLUECHIPFILE "$SBARDIR\\VILDROID\\BUCHIP.TXT"
#define DISCEJECTSOUND "$SBARDIR\\VILDROID\\AUDIO\\OBJECTS\\DDTCPIC1.WAV"
#define THUNDERSOUND "$SBARDIR\\AUDITON\\AUDIO\\EVENTS\\LGHTN1.WAV"

// Static function prototypes.
//
static BOOL VildroidFilter(CBofBitmap *pBmp, CBofRect *pRect);
static BOOL TriFilter(CBofBitmap *pBmp, CBofRect *pRect);
static BOOL ZzazzlFilter(CBofBitmap *pBmp, CBofRect *pRect);
static BOOL HalucinateFilter(CBofBitmap *pBmp, CBofRect *pRect);
static BOOL LightningFilter(CBofBitmap *pBmp, CBofRect *pRect);

// Static data definitions.
//
static CBofBitmap *pTipBmp = nullptr;
static CBofBitmap *pChipBmp = nullptr;
static CBofBitmap *pGrafittiBmp = nullptr;
static CBofBitmap *pTriBmp = nullptr;
static BOOL initDone = FALSE;
static BOOL triinitDone = FALSE;
static BOOL lightninginitDone = FALSE;
static char *buff = nullptr;
static const char *kPrecipString = "Chance Of Precipitation: ";
static const char *kDustString = "Dust Level: ";
static const char *kRadioOnString = "Internal Radio Receiver: On";
static const char *kRadioOffString = "Internal Radio Receiver: Off";
static DWORD dwTimeOfNextBolt = 0;
static CBofSound *pThunder = nullptr;
static const char *voiceNameArray[] = {
	"Voice ID: None",
	"Voice ID: Veeblecoach",
	"Voice ID: Pictureguarder",
	"Voice ID: Commentmaker",
	"Voice ID: Hairtrimmer",
	"Voice ID: President",
	"Voice ID: P.A. Announcer",
	"Voice ID: Playdescriber and Coloradder",
	"Voice ID: Unable to process multiple signals.",
	"Voice ID:"
};
static const CBofRect viewPortRect(80, 10, 559, 369);
static CBofRect viewRect;

#if BOF_WINDOWS
#define GetTimer() (uint32)GetTimer()
#elif BOF_MAC
#define GetTimer() (uint32)(16.66 * TickCount())
#endif

// Filter initialization code.
//
VOID VilInitFilters(CBofBitmap *pBmp) {
	if (!initDone) {
		CHAR szCString[256];
		CBofString cString(szCString, 256);
		cString = VILDROIDTIPFILE;

		MACROREPLACE(cString);
		CBofFile nfile(cString, CBF_READONLY);
		buff = new char[nfile.GetLength() + 1];
		memset(buff, 0, nfile.GetLength() + 1);
		nfile.Read(buff, nfile.GetLength());
		StrReplaceChar(buff, '\n', ' ');
		StrReplaceChar(buff, '\r', ' ');
		pTipBmp = new CBofBitmap((nfile.GetLength() + 1) * 7, 20, pBmp->GetPalette());
#if BOF_MAC
		pTipBmp->FillRect(nullptr, COLOR_WHITE);
#endif
		CBofRect rct(0, 0, (nfile.GetLength() + 1) * 7, 20);
		PaintText(pTipBmp, &rct, buff, VILDROIDTIPSTEXTSIZE, TEXT_BOLD, RGB(107, 0, 255), JUSTIFY_LEFT, FORMAT_DEFAULT);
		nfile.Close();
		delete buff;

		// Grafitti bitmap.
		//
		CHAR szBString[256];
		CBofString cBString(szBString, 256);
		cBString = VILDROIDGRAFITTI;
		MACROREPLACE(cBString);
		pGrafittiBmp = new CBofBitmap(cBString, pBmp->GetPalette());

		// No initialization of the pChipBmp is done here - it's
		// done on the fly inside VildroidFilter.
		//
		// init the timer check for Chip info display
		waitCount = 0;

		// Record the fact that the filter bitmaps have been created.
		//
		initDone = TRUE;
	}
}

VOID TriInitFilters(CBofBitmap *pBmp) {
	// Trisecks sunglasses bitmap.
	//
	CHAR szTriStr[256];
	CBofString cTriStr(szTriStr, 256);
	cTriStr = TRIFILTERBMP;
	MACROREPLACE(cTriStr);
	pTriBmp = new CBofBitmap(cTriStr, pBmp->GetPalette());
	triinitDone = TRUE;
}

VOID LightningInitFilters() {
	if (!lightninginitDone) {
		CHAR szThunderFileName[256];
		CBofString cThunderFileName(szThunderFileName, 256);
		cThunderFileName = THUNDERSOUND;
		MACROREPLACE(cThunderFileName);
		pThunder = new CBofSound(CBofApp::GetApp()->GetMainWindow(), szThunderFileName, SOUND_MIX);
		lightninginitDone = TRUE;
	}
}

VOID DestroyFilters() {
	if (pTipBmp) {
		delete pTipBmp;
		pTipBmp = nullptr;
	}
	if (pGrafittiBmp) {
		delete pGrafittiBmp;
		pGrafittiBmp = nullptr;
	}
	// clean up trisecks bmp
	if (pTriBmp) {
		delete pTriBmp;
		pTriBmp = nullptr;
	}
	// Chip bitmap is destroyed here is the cleanup function because
	// presumably we're being called when the game is ending.
	//
	if (pChipBmp) {
		delete pChipBmp;
		pChipBmp = nullptr;
	}

	// Clean up the lightning filter.
	//
	if (pThunder) {
		delete pThunder;
		pThunder = nullptr;
	}

	// Record the fact that the filter bitmaps need to be instantiated
	// before they can be used again.
	//
	initDone = FALSE;
	triinitDone = FALSE;
	lightninginitDone = FALSE;
}



BOOL DoFilters(const uint16 nFilterId, CBofBitmap *pBmp, CBofRect *pRect) {
	BOOL bReturnValue = FALSE;

	if ((nFilterId & kTriFilter) != 0) {
		bReturnValue = (TriFilter(pBmp, pRect) || bReturnValue);
	}

	if ((nFilterId & kHalucinateFilter) != 0) {
		bReturnValue = (HalucinateFilter(pBmp, pRect) || bReturnValue);
	}

	if ((nFilterId & kVildroidFilter) != 0) {
		bReturnValue = (VildroidFilter(pBmp, pRect) || bReturnValue);
	}

	if ((nFilterId & kZzazzlFilter) != 0) {
		bReturnValue = (ZzazzlFilter(pBmp, pRect) || bReturnValue);
	}

	if ((nFilterId & kLightningFilter) != 0) {
		bReturnValue = (LightningFilter(pBmp, pRect) || bReturnValue);
	}

	return bReturnValue;
}

static CBagVar *g_pHudOn = nullptr;
static CBagVar *g_pDGrafiti = nullptr;
static CBagVar *g_pDRadio = nullptr;
static CBagVar *g_pPrecip = nullptr;
static CBagVar *g_pPrecDecimal = nullptr;
static CBagVar *g_pDust = nullptr;
static CBagVar *g_pDustDecimal = nullptr;
static CBagVar *g_pDVoiceID = nullptr;
static CBagVar *g_pDChipID = nullptr;
static CBagVar *g_pTDig1 = nullptr;
static CBagVar *g_pTDig2 = nullptr;
static CBagVar *g_pTDig3 = nullptr;
static CBagVar *g_pTDig4 = nullptr;

BOOL g_bGetVilVars = TRUE;

// GetVariable is REALLY EXPENSIVE - Don't do it too often
//
static VOID GetVilVars() {
	CHAR szBuf[256];
	szBuf[0] = '\0';
	CBofString cStr(szBuf, 256);

	// check if HUD is on
	cStr = "HUDON";
	g_pHudOn = VARMNGR->GetVariable(cStr);

	cStr = "DGRAFITTI";
	g_pDGrafiti = VARMNGR->GetVariable(cStr);

	cStr = "DRADIO";
	g_pDRadio = VARMNGR->GetVariable(cStr);

	cStr = "PRECIPITATION";
	g_pPrecip = VARMNGR->GetVariable(cStr);

	cStr = "PRECDECIMAL";
	g_pPrecDecimal = VARMNGR->GetVariable(cStr);

	cStr = "DUST";
	g_pDust = VARMNGR->GetVariable(cStr);

	cStr = "DUSTDECIMAL";
	g_pDustDecimal = VARMNGR->GetVariable(cStr);

	cStr = "DVOICEID";
	g_pDVoiceID = VARMNGR->GetVariable(cStr);

	cStr = "DCHIPID";
	g_pDChipID = VARMNGR->GetVariable(cStr);

	cStr = "TDIG1";
	g_pTDig1 = VARMNGR->GetVariable(cStr);

	cStr = "TDIG2";
	g_pTDig2 = VARMNGR->GetVariable(cStr);

	cStr = "TDIG3";
	g_pTDig3 = VARMNGR->GetVariable(cStr);

	cStr = "TDIG4";
	g_pTDig4 = VARMNGR->GetVariable(cStr);
}


// Vildroid filter.
//
static BOOL VildroidFilter(CBofBitmap *pBmp, CBofRect *pRect) {
	CHAR szVBuff2[256];

	if (!initDone) {
		VilInitFilters(pBmp);
	}

	// If get vars for 1st time
	//
	if (g_bGetVilVars) {
		GetVilVars();
		g_bGetVilVars = FALSE;
	}

	if (pRect != nullptr) {
		viewRect = *pRect;

	} else {

		// A null rectangle implies that we're going to filter the
		// entire screen.  Take the bitmap's rectangle and intersect
		// that with the rectangle for the viewport. Filter the resulting
		// rectangle.

		// Now intersect that rectangle with the bitmap's rectangle.
		//
		viewRect.IntersectRect(pBmp->GetRect(), viewPortRect);
	}

	if (g_pHudOn->GetNumValue() == 1) {


		if (g_pDGrafiti->GetNumValue()) {
			CBofRect SrcRect(pGrafittiBmp->GetRect());
			pGrafittiBmp->Paint(pBmp, viewRect.left, viewRect.top, &SrcRect, 1);
		}

		CBofRect rect(viewRect.left, viewRect.top, viewRect.right, viewRect.top + 20);

		// Display internal radio setting.
		//

		if (g_pDRadio->GetNumValue()) {
			PaintText(pBmp, &rect, kRadioOnString, VILDROIDSTATSTEXTSIZE, TEXT_BOLD, RGB(0, 255, 6), JUSTIFY_LEFT, FORMAT_DEFAULT);
		} else {
			PaintText(pBmp, &rect, kRadioOffString, VILDROIDSTATSTEXTSIZE, TEXT_BOLD, RGB(0, 255, 6), JUSTIFY_LEFT, FORMAT_DEFAULT);
		}

		// Display chance of precipitation.
		//
		Common::sprintf_s(szVBuff2, "%s%d.%d%%", kPrecipString, g_pPrecip->GetNumValue(), g_pPrecDecimal->GetNumValue());
		CBofRect cleanRect((viewRect.right - 250), viewRect.top, viewRect.right - 5, viewRect.top + 20);
		PaintText(pBmp, &cleanRect, szVBuff2, VILDROIDSTATSTEXTSIZE, TEXT_BOLD, RGB(0, 255, 6), JUSTIFY_RIGHT, FORMAT_DEFAULT);

		// Display dust level.
		//
		Common::sprintf_s(szVBuff2, "%s%d.%dp/cmm", kDustString, g_pDust->GetNumValue(), g_pDustDecimal->GetNumValue());
		cleanRect.bottom += 20;
		cleanRect.top += 20;
		PaintText(pBmp, &cleanRect, szVBuff2, VILDROIDSTATSTEXTSIZE, TEXT_BOLD, RGB(0, 255, 6), JUSTIFY_RIGHT, FORMAT_DEFAULT);

		int voiceId = g_pDVoiceID->GetNumValue();
		const char *pVoiceIdString = voiceNameArray[voiceId];

		rect.top += 20;
		rect.bottom += 20;
		PaintText(pBmp, &rect, pVoiceIdString, VILDROIDSTATSTEXTSIZE, TEXT_BOLD, RGB(255, 193, 0), JUSTIFY_LEFT, FORMAT_DEFAULT);

		CBofRect srcTipRect;

		srcTipRect.left = 0;
		srcTipRect.right = viewRect.right - viewRect.left;
		srcTipRect.top = 0;
		srcTipRect.bottom = 20;

		pTipBmp->ScrollLeft(VILDROIDTIPSCROLLSPEED, nullptr);
		rect.left = viewRect.left;
		rect.right = viewRect.right;
		rect.top = viewRect.bottom - 20;
		rect.bottom = viewRect.bottom;
		pTipBmp->Paint(pBmp, &rect, &srcTipRect, 0);

		// moved up here to use chipID later on bar
		int chipID = g_pDChipID->GetNumValue();

		if (CMainWindow::chipdisp == FALSE) {
			switch (chipID) {
			case 0: {
				break;
			};
			case 1: {
				if (pChipBmp != nullptr)
					delete pChipBmp;

				CHAR szCString[256];                // performance improvement
				CBofString cString(szCString, 256);
				cString = GREENCHIPFILE;

				MACROREPLACE(cString);
				CBofFile nfile(cString, CBF_READONLY);
				buff = new char[nfile.GetLength() + 1];
				memset(buff, 0, nfile.GetLength() + 1);
				pChipBmp = new CBofBitmap(VILDROIDCHIPTEXTWIDTH, 300, pBmp->GetPalette());
				nfile.Read(buff, nfile.GetLength());
				CBofRect txtRect(0, 0, VILDROIDCHIPTEXTWIDTH, 18);
				uint32 test = 0;
				char *pBuff1 = buff;
				char *pBuff2 = buff;
				BOOL bFinished = FALSE;

				while (bFinished != TRUE) {
					while (*pBuff1 != '\n' && *pBuff1 != '\r' && bFinished != TRUE) {
						test++;
						pBuff1++;
						if (test >= nfile.GetLength())
							bFinished = TRUE;

					}
					if (test >= nfile.GetLength())
						bFinished = TRUE;
					else {
						*pBuff1 = '\0';
						PaintText(pChipBmp, &txtRect, pBuff2, VILDROIDTIPSTEXTSIZE, TEXT_BOLD, RGB(255, 7, 0), JUSTIFY_CENTER, FORMAT_TOP_CENTER);
						pBuff2 = pBuff1 + 1;
						txtRect.top += 18;
						txtRect.bottom += 18;
					}
				}
				nfile.Close();
				CMainWindow::chipdisp = TRUE;
				delete buff;
				break;
			};
			case 2: {
				if (pChipBmp != nullptr)
					delete pChipBmp;

				CHAR szCString[256];
				CBofString cString(szCString, 256);
				cString = BLUECHIPFILE;

				MACROREPLACE(cString);
				CBofFile nfile(cString, CBF_READONLY);
				buff = new char[nfile.GetLength() + 1];
				memset(buff, 0, nfile.GetLength() + 1);
				pChipBmp = new CBofBitmap(VILDROIDCHIPTEXTWIDTH, 300, pBmp->GetPalette());
				nfile.Read(buff, nfile.GetLength());
				CBofRect txtRect(0, 0, VILDROIDCHIPTEXTWIDTH, 18);
				uint32 test = 0;
				char *pBuff1 = buff;
				char *pBuff2 = buff;
				BOOL bFinished = FALSE;

				while (bFinished != TRUE) {
					while (*pBuff1 != '\n' && *pBuff1 != '\r' && bFinished != TRUE) {
						test++;
						pBuff1++;
						if (test >= nfile.GetLength())
							bFinished = TRUE;

					}
					if (test >= nfile.GetLength())
						bFinished = TRUE;
					else {
						*pBuff1 = '\0';
						PaintText(pChipBmp, &txtRect, pBuff2, VILDROIDTIPSTEXTSIZE, TEXT_BOLD, RGB(255, 7, 0), JUSTIFY_CENTER, FORMAT_TOP_CENTER);
						pBuff2 = pBuff1 + 1;
						txtRect.top += 18;
						txtRect.bottom += 18;
					}
				}
				nfile.Close();
				CMainWindow::chipdisp = TRUE;
				delete buff;
				break;
			};
			case 3: {
				if (pChipBmp != nullptr) {
					delete pChipBmp;
					pChipBmp = nullptr;
				}
				CMainWindow::chipdisp = TRUE;
				break;
			};
			};
		} else {
			if (g_pDChipID->GetNumValue() == 3) {
				CBofRect txtRect(viewRect);
				DWORD lDiff;
				uint32 timer = GetTimer();

				if (waitCount == 0)
					waitCount = timer;

				lDiff = (timer - waitCount) / 1000;

				switch (lDiff) {
				case 0:
				case 1:
					PaintText(pBmp, &txtRect, "VIMM chip accepted", VILDROIDTIPSTEXTSIZE, TEXT_BOLD, RGB(255, 7, 0), JUSTIFY_CENTER, FORMAT_TOP_CENTER);
					break;

				case 2:
				case 3:
					PaintText(pBmp, &txtRect, "Mark IV OS initialized", VILDROIDTIPSTEXTSIZE, TEXT_BOLD, RGB(255, 7, 0), JUSTIFY_CENTER, FORMAT_TOP_CENTER);
					break;

				case 4:
				case 5:
					PaintText(pBmp, &txtRect, "Reading flashbank....", VILDROIDTIPSTEXTSIZE, TEXT_BOLD, RGB(255, 7, 0), JUSTIFY_CENTER, FORMAT_TOP_CENTER);
					break;

				case 6:
				case 7:
					PaintText(pBmp, &txtRect, "Process completed", VILDROIDTIPSTEXTSIZE, TEXT_BOLD, RGB(255, 7, 0), JUSTIFY_CENTER, FORMAT_TOP_CENTER);
					break;

				case 8:
				case 9:
					PaintText(pBmp, &txtRect, "1. General Knowledge", VILDROIDTIPSTEXTSIZE, TEXT_BOLD, RGB(255, 7, 0), JUSTIFY_CENTER, FORMAT_TOP_CENTER);
					break;

				case 10:
				case 11:
					PaintText(pBmp, &txtRect, "2. Vildroid History", VILDROIDTIPSTEXTSIZE, TEXT_BOLD, RGB(255, 7, 0), JUSTIFY_CENTER, FORMAT_TOP_CENTER);
					break;

				case 12:
				case 13:
					PaintText(pBmp, &txtRect, "3. Recipe DataBank J12", VILDROIDTIPSTEXTSIZE, TEXT_BOLD, RGB(255, 7, 0), JUSTIFY_CENTER, FORMAT_TOP_CENTER);
					break;

				case 14:
				case 15:
					PaintText(pBmp, &txtRect, "4. Personal Database C238-87565", VILDROIDTIPSTEXTSIZE, TEXT_BOLD, RGB(255, 7, 0), JUSTIFY_CENTER, FORMAT_TOP_CENTER);
					break;

				case 16:
				case 17:
					PaintText(pBmp, &txtRect, "5. Veebleball Strategy Kit", VILDROIDTIPSTEXTSIZE, TEXT_BOLD, RGB(255, 7, 0), JUSTIFY_CENTER, FORMAT_TOP_CENTER);
					break;

				case 18:
				case 19:
					PaintText(pBmp, &txtRect, "6. Termite Infestation", VILDROIDTIPSTEXTSIZE, TEXT_BOLD, RGB(255, 7, 0), JUSTIFY_CENTER, FORMAT_TOP_CENTER);
					break;

				case 20:
				case 21:
					PaintText(pBmp, &txtRect, "7. Latex Glove Sizing Chart", VILDROIDTIPSTEXTSIZE, TEXT_BOLD, RGB(255, 7, 0), JUSTIFY_CENTER, FORMAT_TOP_CENTER);
					break;

				case 22:
				case 23:
					PaintText(pBmp, &txtRect, "8. Cleaning Dead Bugs Out From Behind Storm Windows", VILDROIDTIPSTEXTSIZE, TEXT_BOLD, RGB(255, 7, 0), JUSTIFY_CENTER, FORMAT_TOP_CENTER);
					break;

				case 24:
				case 25:
					PaintText(pBmp, &txtRect, "9. Algorithms 1233B thru 1245DD: 12 Steps to Whiter Tiles", VILDROIDTIPSTEXTSIZE, TEXT_BOLD, RGB(255, 7, 0), JUSTIFY_CENTER, FORMAT_TOP_CENTER);
					break;

				case 26:
				case 27:
				case 28:
				case 29: {
					PaintText(pBmp, &txtRect,
						BuildString("You have been assigned Maintenance Mode PIN: %d%d%d%d",
						g_pTDig1->GetNumValue(), g_pTDig2->GetNumValue(),
						g_pTDig3->GetNumValue(), g_pTDig4->GetNumValue()),
						VILDROIDTIPSTEXTSIZE, TEXT_BOLD, RGB(255, 7, 0),
						JUSTIFY_CENTER, FORMAT_TOP_CENTER);
					break;
				}

				default: {
					CMainWindow::chipdisp = FALSE;
					waitCount = 0;
					g_pDChipID->SetValue(0);
					break;
				}

				}

			} else {
				// Chip is Green or Blue (ID 1 or 2)
				if (pChipBmp != nullptr) {
					int rdef = viewRect.Width() - VILDROIDCHIPTEXTWIDTH;
					int tdef = viewRect.Height() - 300;
					CBofRect tmprct(0, 0, VILDROIDCHIPTEXTWIDTH, 300);                 // (tdef/2)

					pChipBmp->Paint(pBmp, ((rdef / 2) + viewRect.left), (tdef + viewRect.top), &tmprct, 0);
				}

				if (waitCount == 0)
					waitCount = GetTimer();

				if ((GetTimer() - waitCount) > 15000) {
					CMainWindow::chipdisp = FALSE;
					waitCount = 0;
					g_pDChipID->SetValue(0);

					CHAR szCString[256];
					CBofString cString(szCString, 256);
					cString = DISCEJECTSOUND;
					MACROREPLACE(cString);
					BofPlaySound(cString, SOUND_WAVE | SOUND_MIX);
					CBagStorageDev *pWieldSDev = nullptr;
					pWieldSDev = SDEVMNGR->GetStorageDevice("BWIELD_WLD");
					if (chipID == 1)
						pWieldSDev->ActivateLocalObject("GREENCHIP");
					else
						pWieldSDev->ActivateLocalObject("BLUECHIP");
				}
			}
		}
	}

	return TRUE;
}


// Trisecks filter
//
static BOOL TriFilter(CBofBitmap *pBmp, CBofRect *pRect) {
	if (!triinitDone) {
		TriInitFilters(pBmp);
	}

	if (pRect != nullptr) {
		viewRect = *pRect;
	} else {

		// A null rectangle implies that we're going to filter the
		// entire screen.  Take the bitmap's rectangle and intersect
		// that with the rectangle for the viewport. Filter the resulting
		// rectangle.

		// Now intersect that rectangle with the bitmap's rectangle.
		//
		viewRect.IntersectRect(pBmp->GetRect(), viewPortRect);
	}

	if (VARMNGR->GetVariable("GLASSESON")->GetNumValue()) {
		CBofRect SrcRect(pTriBmp->GetRect());
		pTriBmp->Paint(pBmp, viewRect.left, viewRect.top, &SrcRect, 1);
	}
	return TRUE;
}

// Zzazzlvision filter.
//
static BOOL ZzazzlFilter(CBofBitmap *pBmp, CBofRect *pRect) {
	CBagVar *pVar;

	CHAR szZBuff[256];
	CBofString zStr(szZBuff, 256);
	BOOL bZzazzlVision = FALSE;

	if (pRect != nullptr) {
		viewRect = *pRect;
	} else {
		// A null rectangle implies that we're going to filter the
		// entire screen.  Take the bitmap's rectangle and intersect
		// that with the rectangle for the viewport. Filter the resulting
		// rectangle.

		// Now intersect that rectangle with the bitmap's rectangle.
		//
		viewRect.IntersectRect(pBmp->GetRect(), viewPortRect);
	}

	zStr = "ZZAZZLVISION";
	if ((pVar = VARMNGR->GetVariable(zStr)) != nullptr) {

		bZzazzlVision = TRUE;
		if (pVar->GetNumValue() > 0) {
			CMainWindow::SetZzazzlVision(TRUE);             // zzazzl paint is on in the script
			int dx = viewRect.Width() / 3;  // + 1;
			int dy = viewRect.Height() / 3; // + 1;
			CBofPalette *pPal = pBmp->GetPalette();

			CBofBitmap *pMiniBitmap;

			if ((pMiniBitmap = new CBofBitmap(dx, dy, pPal)) != nullptr) {
				CBofRect dstRect(viewRect);
				CBofRect srcRect = pMiniBitmap->GetRect();
				pBmp->Paint(pMiniBitmap, &srcRect, &dstRect);

				CBofRect &filterRect = CMainWindow::GetFilterRect();
				filterRect.SetRect(viewRect.left, viewRect.top, viewRect.left + dx, viewRect.top + dy);
#ifdef OLDSTUFF
				// this could be made a bit faster with bitmap strips
				int i, j, x, y = viewRect.top;
				for (i = 0; i < 3; ++i) {
					if (i == 1) {
						j = 1;
						x = viewRect.left;
					} else {
						j = 0;
						x = viewRect.left - (dx >> 1);
					}
					for (; j < 4; ++j) {
						pMiniBitmap->Paint(pBmp, x, y);
						x += dx;
					}
					y += dy;
				}
				delete pMiniBitmap;
#else
				int i, j, x, y = viewRect.top;
				for (i = 0; i < 3; ++i) {
					if (i == 1) {
						j = 0;
						x = viewRect.left;
					} else {
						j = 1;
						x = viewRect.left + (dx >> 1);
					}
					for (; j < 3; ++j) {
						pMiniBitmap->Paint(pBmp, x, y);
						x += dx;
					}
					y += dy;
				}
				delete pMiniBitmap;
#endif
			}
		}
	}

	return bZzazzlVision;
}

// Halucination filter.
//
static BOOL HalucinateFilter(CBofBitmap *pBmp, CBofRect *pRect) {
	CHAR szHBuff[256];
	CBofString hStr(szHBuff, 256);
	BOOL bHallucinating = FALSE;

	if (pRect != nullptr) {
		viewRect = *pRect;
	} else {
		// A null rectangle implies that we're going to filter the
		// entire screen.  Take the bitmap's rectangle and intersect
		// that with the rectangle for the viewport. Filter the resulting
		// rectangle.

		// Now intersect that rectangle with the bitmap's rectangle.
		//
		viewRect.IntersectRect(pBmp->GetRect(), viewPortRect);
	}

	hStr = "HALLUCINATE";

	if (VARMNGR->GetVariable(hStr)->GetNumValue() > 0) {
		bHallucinating = TRUE;
		CBofPalette *pPal = pBmp->GetPalette();
		pPal = pBmp->GetPalette();
		CBofBitmap *pTempBitmap = new CBofBitmap(viewRect.Width(), viewRect.Height(), pPal);
		CBofRect tempRect = pTempBitmap->GetRect();
		CBofRect srcRect(viewRect);
		CBofRect dstRect = tempRect;
		pBmp->Paint(pTempBitmap, &dstRect, &srcRect);   // Copy the Screen's Bmp into Temp
		INT nShiftAmount = 0;
		INT y;                          // Step through strips of bmp
		for (y = tempRect.top; y < tempRect.bottom; y += 4) {
			srcRect.SetRect(0, y, tempRect.right - nShiftAmount, y + 4); // Get everything over one
			dstRect.SetRect(viewRect.left + nShiftAmount, viewRect.top + y,
			                viewRect.right, (viewRect.top + y) + 4);
			pTempBitmap->Paint(pBmp, &dstRect, &srcRect);
			srcRect.SetRect(tempRect.right - nShiftAmount, y, tempRect.right, y + 4);
			dstRect.SetRect(viewRect.left, viewRect.top + y,
			                viewRect.left + nShiftAmount, (viewRect.top + y) + 4);
			pTempBitmap->Paint(pBmp, &dstRect, &srcRect);
			// I'm sure there's some nerdy math formula that does
			//...this all pretty-like -- will fix it if it comes to me
			// Change the amount of shift depending on the row we're in
			if (((y / 4) % 20) < 3)
				nShiftAmount += 2;
			else if (((y / 4) % 20) < 8)
				nShiftAmount += 5;
			else if (((y / 4) % 20) < 10)
				nShiftAmount += 3;
			else if (((y / 4) % 20) < 15)
				nShiftAmount -= 3;
			else if (((y / 4) % 20) < 18)
				nShiftAmount -= 5;
			else
				nShiftAmount -= 2;
		}
		delete pTempBitmap;
	}

	return bHallucinating;
}

static BOOL LightningFilter(CBofBitmap *pBmp, CBofRect *pRect) {
	Assert(pBmp != nullptr);

	BOOL bReturnValue = TRUE;

	// See if lightning is on in this storage device.
	//
	CHAR szVBuf[256];
	CBofString vStr(szVBuf, 256);
	vStr = "LIGHTNINGDELAY";
	CBagVar *pVar = VARMNGR->GetVariable(vStr);
	INT nLightningDelay = 0;

	if (pVar != nullptr) {
		nLightningDelay = pVar->GetNumValue();
	}

	if (nLightningDelay > 0) {
		if (!lightninginitDone) {
			LightningInitFilters();
		}

		// Check to see if it's time to "flash" a bolt of lightning.
		//
		if (dwTimeOfNextBolt < GetTimer()) {
			// Time to paint the effect of a lightning bolt
			// flash and play the sound of a thunderbolt.
			//

			if (pRect != nullptr) {
				viewRect = *pRect;
			} else {
				// A null rectangle implies that we're going to filter the
				// entire screen.  Take the bitmap's rectangle and intersect
				// that with the rectangle for the viewport. Filter the resulting
				// rectangle.

				// Now intersect that rectangle with the bitmap's rectangle.
				//
				viewRect.IntersectRect(pBmp->GetRect(), viewPortRect);
			}

			// To give the illusion of a lightning bolt strike,
			// we'll spin through the bitmap and coerce pixels which
			// are black to be white and pixels which are not black
			// be black.
			//
			INT nWidth = viewRect.Width();
			INT nHeight = viewRect.Height();
			INT i, j;

			// Need to lock down this bitmap to make sure we can get it's bits
			//
			pBmp->Lock();

			for (i = 0; i < nHeight; i++) {
				UBYTE *pPixel = pBmp->GetPixelAddress(viewRect.left, viewRect.top + i);

				// Fix this such that it uses predefined constants, makes for much
				// better lightning on the mac.
				for (j = 0; j < nWidth; j++, pPixel++) {
					if (*pPixel == COLOR_BLACK) {
						*pPixel = COLOR_BLACK;
					} else {
						*pPixel = COLOR_WHITE;
					}
				}
			}

			// Don't need a lock on it anymore
			pBmp->UnLock();

			// Let's hear the thunder!
			//
			pThunder->Play();

			// Set the time that the next bolt of lightning will occur.
			// If only nature were so precise...
			//
			dwTimeOfNextBolt = GetTimer() + nLightningDelay;
		}

	}
	return bReturnValue;
}

} // namespace SpaceBar
} // namespace Bagel
