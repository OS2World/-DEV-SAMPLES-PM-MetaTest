/*---------------------------------
   STAR5.C -- Draws 5-Pointed Star
 ----------------------------------*/
/*
Modified to write a PM metafile which can be viewed by the PM Picture
displayer within the utilities directory of the OS/2 Desktop.
*/

#define INCL_GPI

#include <os2.h>

MRESULT EXPENTRY ClientWndProc (HWND, ULONG, MPARAM, MPARAM) ;

/* Added for metafile */
DEVOPENSTRUC dop;

HDC			hdc;
HDC			hdcMeta;
HPS			hpsMeta;
HMF			hmf;
SIZEL		sizlPage;
POINTL		ptl1, ptl2;
/* End of metafile stuff */

int main (void)
     {
     static CHAR  szClientClass [] = "Star5" ;
     static ULONG flFrameFlags = FCF_TITLEBAR      | FCF_SYSMENU |
                                 FCF_SIZEBORDER    | FCF_MINMAX  |
                                 FCF_SHELLPOSITION | FCF_TASKLIST ;
     HAB          hab ;
     HMQ          hmq ;
     HWND         hwndFrame, hwndClient ;
     QMSG         qmsg ;

     hab = WinInitialize (0) ;

     hmq = WinCreateMsgQueue (hab, 0) ;

     WinRegisterClass (hab, (PCSZ) szClientClass, (PFNWP) ClientWndProc, CS_SIZEREDRAW, 0) ;

     hwndFrame = WinCreateStdWindow (HWND_DESKTOP, WS_VISIBLE,
                                     &flFrameFlags, (PCSZ) szClientClass, NULLHANDLE,
                                     0L, NULLHANDLE, 0, &hwndClient) ;

/* Added for metafile */
	dop.pszLogAddress = NULL;
	dop.pszDriverName = (PSZ) "DISPLAY";
	dop.pdriv = NULL;
	dop.pszDataType = NULL;

	hdcMeta = DevOpenDC(hab,
				OD_METAFILE,
				(PCSZ) "*",
				4L,
				(PDEVOPENDATA) &dop,
				hdc);

	hpsMeta = GpiCreatePS(hab,
				hdcMeta,
				&sizlPage,
				PU_PELS | GPIA_ASSOC);

/* Draw box in metafile */

	GpiSetColor(hpsMeta, CLR_CYAN);
	ptl1.x = 150;
	ptl1.y = 200;
	GpiMove(hpsMeta, &ptl1);
	ptl2.x = 300;
	ptl2.y = 275;
	GpiBox(hpsMeta, DRO_FILL, &ptl2, 0L, 0L);

	GpiSetColor(hpsMeta, CLR_GREEN);
	ptl1.x = 300;
	ptl1.y = 200;
	GpiMove(hpsMeta, &ptl1);
	ptl2.x = 390;
	ptl2.y = 275;
	GpiBox(hpsMeta, DRO_FILL, &ptl2, 0L, 0L);

	GpiSetColor(hpsMeta, CLR_YELLOW);
	ptl1.x = 390;
	ptl1.y = 200;
	GpiMove(hpsMeta, &ptl1);
	ptl2.x = 530;
	ptl2.y = 275;
	GpiBox(hpsMeta, DRO_FILL, &ptl2, 0L, 0L);

	GpiSetColor(hpsMeta, CLR_PINK);
	ptl1.x = 175;
	ptl1.y = 230;
	GpiMove(hpsMeta, &ptl1);
	GpiCharString(hpsMeta, 41L,
	(PCCH) "This is a sample Metafile created by Dan.");

	GpiAssociate(hpsMeta, NULLHANDLE);
	hmf = DevCloseDC(hdcMeta);

	/* Sabve metafile to disk */
	GpiSaveMetaFile(hmf, (PCSZ) "box.met");

/* End of metafile code */

     while (WinGetMsg (hab, &qmsg, NULLHANDLE, 0, 0))
          WinDispatchMsg (hab, &qmsg) ;

     WinDestroyWindow (hwndFrame) ;
     WinDestroyMsgQueue (hmq) ;
     WinTerminate (hab) ;
     return 0 ;
     }



MRESULT EXPENTRY ClientWndProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
     {
     static POINTL aptlStar[5] = {{-59,-81}, {0,100}, {59,-81}, {-95,31}, {95,31} } ;
     static SHORT  cxClient, cyClient ;
     HPS           hps ;
     POINTL        aptl[5] ;
     SHORT         sIndex ;

     switch (msg)
	  {
          case WM_SIZE:
               cxClient = SHORT1FROMMP (mp2) ;
               cyClient = SHORT2FROMMP (mp2) ;
               return 0 ;

          case WM_PAINT:

               hps = WinBeginPaint (hwnd, NULLHANDLE, NULLHANDLE) ;
               GpiErase (hps) ;

               for (sIndex = 0 ; sIndex < 5 ; sIndex++)
                    {
                    aptl[sIndex].x = cxClient / 2 + cxClient *
                                                 aptlStar[sIndex].x / 200 ;
                    aptl[sIndex].y = cyClient / 2 + cyClient *
                                                 aptlStar[sIndex].y / 200 ;
                    }
               GpiMove (hps, aptl + 4) ;
               GpiPolyLine (hps, 5L, aptl) ;

               WinEndPaint (hps) ;
               return 0 ;
          }
     return WinDefWindowProc (hwnd, msg, mp1, mp2) ;
     }
