/* $Id: UniSorter.c,v 1.1.1.1 2003/02/10 23:15:15 tim Exp $
 *
 * Uni Sorter
 * Software to demonstrate and visualize some sorting algorithms
 * Copyright (C) 2002 by Tim Niemueller <tim@niemueller.de>
 * Website: http://www.niemueller.de/software/palm/unisorter/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * Created 2002/07/26
 */

#include "UniSorter.h"
#include "color.h"
#include "gadget.h"
#include "quicksort.h"
#include "insertionsort.h"
#include "selectionsort.h"
#include "bubblesort.h"
#include "shellsort.h"
#include "mergesort.h"
#include "heapsort.h"
#include "shakersort.h"
#include "radixsort.h"
#include "countsort.h"

Boolean gIsSorted=false, gBreakSort=false;
Int8 *gValues=NULL;
UInt16 gSleep=5;

/***********************************************************************
 * FUNCTION:    GetObjectPtr
 * DESCRIPTION: This routine returns a pointer to an object in the current
 *              form.
 * PARAMETERS:  formId - id of the form to display
 ***********************************************************************/
void * GetObjectPtr(UInt16 objectID) {
	FormPtr frmP = FrmGetActiveForm();
	return (FrmGetObjectPtr(frmP, FrmGetObjectIndex(frmP, objectID)));
}


/***********************************************************************
 * function is called at program start
 * you can put your own initialization jobs there
 ***********************************************************************/
static UInt16 StartApplication (void) {
  Err err = 0;
  UInt32 requiredDepth = APP_COLORDEPTH;
  UInt32 currentDepth = 0;
  Boolean hasColor=false;
  UInt16 prefSize=sizeof(gSleep);

	// Initialize the random number seed;
	SysRandom( TimGetSeconds() );

  // Set Display mode
  err = WinScreenMode(winScreenModeGet, NULL, NULL, &currentDepth, &hasColor);
  if (!hasColor && (currentDepth < requiredDepth))
    err = WinScreenMode(winScreenModeSet, NULL, NULL, &requiredDepth, &hasColor);

  gValues=(Int8 *)MemPtrNew(sizeof(Int8) * (VALUES_NUM + 2)); // +2 because of marker elements


  if (PrefGetAppPreferences(APP_CREATOR, PREFS_SPEED, &gSleep, &prefSize, false) == noPreferenceFound)
    gSleep=3;

  return (err);
}

/***********************************************************************
 * function is checking ROM version of the palmos operating system
 * if ROM version is less then required the result of this function is
 * sysErrRomIncompatible
 ***********************************************************************/
static Err RomVersionCompatible (UInt32 requiredVersion, UInt16 launchFlags) {
	UInt32 romVersion;

	// See if we're on in minimum required version of the ROM or later.
	FtrGet(sysFtrCreator, sysFtrNumROMVersion, &romVersion);
	if (romVersion < requiredVersion) {
		if ((launchFlags & (sysAppLaunchFlagNewGlobals | sysAppLaunchFlagUIApp)) ==
  			(sysAppLaunchFlagNewGlobals | sysAppLaunchFlagUIApp)) {
			FrmAlert (ALERT_ROMIncompatible);

			// PalmOS before 3.5 will continuously relaunch this app unless we switch to
			// another safe one.
			AppLaunchWithCommand(sysFileCDefaultApp, sysAppLaunchCmdNormalLaunch, NULL);
    }

    return (sysErrRomIncompatible);
  }

  return (0);
}

/***********************************************************************
 * function for main form initialization
 * you can put your initialization stuff there
 * e.g. initial settings for controls and labels
 ***********************************************************************/
static void MainFormInit (FormPtr frm){
	UInt32 romVersion;

	FtrGet(sysFtrCreator, sysFtrNumROMVersion, &romVersion);
  if (romVersion < 0x04000000) TNSetColorMode(COLORMODE_35);
  else TNSetColorMode(COLORMODE_40);

  FrmSetGadgetData(frm, FrmGetObjectIndex(frm, GADGET_main), gValues);
  GadgetSet(frm, GADGET_main);
  GadgetFillRandom();
  FrmSetGadgetHandler(frm, FrmGetObjectIndex(frm, GADGET_main), GadgetHandler);

  CtlSetValue(GetObjectPtr(BUTTON_quick), 1);
}

/***********************************************************************
 * handling for the main drop down menu actions
 ***********************************************************************/
Boolean HandleMenuEvent (UInt16 command){
  Boolean handled = false;

  MenuEraseStatus(0);

  switch (command) {
    case MENUITEM_about:
      FrmDoDialog(FrmInitForm(FORM_about));
      handled=true;
      break;

    default:
      break;
  }

  return handled;
}



/***********************************************************************
 * Set the speed
 ***********************************************************************/
static void PrefSpeed(void) {
  FormPtr frm, previousForm=FrmGetActiveForm();
  ControlType *ctl;
  UInt16 hitButton;

  frm = FrmInitForm(FORM_speed);
  FrmSetActiveForm(frm);
  ctl = GetObjectPtr(SLIDER_speed);

  CtlSetSliderValues(ctl, NULL, NULL, NULL, &gSleep);

  hitButton = FrmDoDialog(frm);

  if (hitButton == BUTTON_speed_ok) {
    CtlGetSliderValues(ctl, NULL, NULL, NULL, &gSleep);
  }

  if (previousForm)  FrmSetActiveForm(previousForm);
  FrmDeleteForm(frm);

}


/***********************************************************************
 * handling for form and control actions
 * menu actions are forwarded to MainFormDoCommand
 ***********************************************************************/
static Boolean MainFormHandleEvent (EventPtr event){
  FormType *frm=FrmGetActiveForm();
  Boolean handled = false;

  if (event->eType == ctlSelectEvent) {
    // button handling
    handled = true;
    switch (event->data.ctlSelect.controlID) {

      case BUTTON_run:
        if (! gIsSorted) {
          ControlType *ctl;
          UInt16 i;

          gBreakSort=false;

          FrmHideObject(frm, FrmGetObjectIndex(frm, BUTTON_run));
          FrmHideObject(frm, FrmGetObjectIndex(frm, BUTTON_reset));
          FrmHideObject(frm, FrmGetObjectIndex(frm, BUTTON_speed));
          FrmHideObject(frm, FrmGetObjectIndex(frm, BUTTON_help));
          FrmHideObject(frm, FrmGetObjectIndex(frm, BUTTON_info));
          FrmShowObject(frm, FrmGetObjectIndex(frm, BUTTON_break));

          for (i = ALGOS_FIRST; i < ALGOS_FIRST + ALGOS_NUM; ++i) {
            ctl=GetObjectPtr(i);
            CtlSetEnabled(ctl, false);
          }

          switch (FrmGetObjectId(frm, FrmGetControlGroupSelection(frm, GROUP_algo))) {
            case BUTTON_quick:
              quicksort(gValues);
              break;

            case BUTTON_quickm:
              quicksort_median(gValues);
              break;

            case BUTTON_quickr:
              quicksort_rect(gValues);
              break;

            case BUTTON_insert:
              insertionsort(gValues);
              break;

            case BUTTON_select:
              selectionsort(gValues);
              break;

            case BUTTON_bubble:
              bubblesort(gValues);
              break;

            case BUTTON_shell:
              shellsort(gValues);
              break;

            case BUTTON_merge:
              mergesort(gValues);
              break;

            case BUTTON_heap:
              heapsort(gValues);
              break;

            case BUTTON_shaker:
              shakersort(gValues);
              break;

            case BUTTON_radix:
              radixsort(gValues);
              break;

            case BUTTON_count:
              countsort(gValues);
              break;

            default:
              break;
          }
          gIsSorted=true;

          FrmHideObject(frm, FrmGetObjectIndex(frm, BUTTON_break));
          FrmShowObject(frm, FrmGetObjectIndex(frm, BUTTON_run));
          FrmShowObject(frm, FrmGetObjectIndex(frm, BUTTON_reset));
          FrmShowObject(frm, FrmGetObjectIndex(frm, BUTTON_speed));
          FrmShowObject(frm, FrmGetObjectIndex(frm, BUTTON_help));
          FrmShowObject(frm, FrmGetObjectIndex(frm, BUTTON_info));

          for (i = ALGOS_FIRST; i < ALGOS_FIRST + ALGOS_NUM; ++i) {
            ctl=GetObjectPtr(i);
            CtlSetEnabled(ctl, true);
          }


        } else FrmAlert(ALERT_sorted);
        break;

      case BUTTON_reset:
        GadgetFillRandom();
        gIsSorted=false;
        break;

      case BUTTON_break:
        gBreakSort=true;
        break;

      case BUTTON_speed:
        PrefSpeed();
        break;

      case BUTTON_help:
        FrmHelp(HELP_main);
        break;

      case BUTTON_info:
        FrmDoDialog(FrmInitForm(FORM_about));
        break;

      default:
        break;
      }
    } else if (event->eType == menuEvent) {
      // forwarding of menu events
      return HandleMenuEvent(event->data.menu.itemID);
    } else if (event->eType == frmUpdateEvent) {
      // redraws the form if needed
      FrmDrawForm (frm);
      handled = true;
    } else if (event->eType == frmOpenEvent) {
      // initializes and draws the form at program launch
      MainFormInit (frm);
      FrmDrawForm (frm);

      handled = true;
    } else if (event->eType == frmCloseEvent) {
      // this is done if program is closed
    }

  return (handled);
}


/***********************************************************************
 * chooses an displays the requested form
 ***********************************************************************/
static Boolean AppHandleEvent( EventPtr eventP) {
	UInt16 formId;
	FormPtr frmP;

	switch (eventP->eType) {
  	case frmLoadEvent:
      // Load the form resource.
		  formId = eventP->data.frmLoad.formID;
		  frmP = FrmInitForm(formId);
		  FrmSetActiveForm(frmP);

      // Set the event handler for the form.  The handler of the currently
      // active form is called by FrmHandleEvent each time is receives an
      // event.
		  switch (formId) {
			  case FORM_main:
				  FrmSetEventHandler(frmP, MainFormHandleEvent);
				  break;

  				ErrNonFatalDisplay("Invalid Form Load Event");
		  		break;
			}
		  break;

	  default:
		  return false;
	}
	return true;
}


/***********************************************************************
 * Sleep for sort functions. put that far down so that we don't need
 * forward declarations for AppHandleEvent...
 ***********************************************************************/
void Sleep(void) {
  if (gSleep && ! gBreakSort) {
    EventType event;
    Err error;
    UInt16 i;

    // We use this weird looking for loop to multiply time we sleep to
    // have a better reaction to events... Since this function is meant to
    // slow down it doesn't hurt...
    for (i=0; i < gSleep * 9; ++i) {

      EvtGetEvent(&event, 0);
      while (event.eType != nilEvent) {
  		  if (! SysHandleEvent(&event))
  		  	if (! MenuHandleEvent(0, &event, &error))
	  			  if (! AppHandleEvent(&event))
  	  				FrmDispatchEvent(&event);
        EvtGetEvent(&event, 0);
      }

      SysTaskDelay((UInt16)(SysTicksPerSecond() / 100));
    }
  }
}



/***********************************************************************
 * main event loop; loops until appStopEvent is caught
 ***********************************************************************/
static void AppEventLoop(void){
	UInt16 error;
	EventType event;


	do {
		EvtGetEvent(&event, evtWaitForever);


		if (! SysHandleEvent(&event))
			if (! MenuHandleEvent(0, &event, &error))
				if (! AppHandleEvent(&event))
					FrmDispatchEvent(&event);

// Check the heaps after each event
		#if EMULATION_LEVEL != EMULATION_NONE
			MemHeapCheck(0);
			MemHeapCheck(1);
		#endif

	} while (event.eType != appStopEvent);

}

/***********************************************************************
 * application is finished, so we have to clean the desktop behind us
 ***********************************************************************/
static void StopApplication (void){
	FrmCloseAllForms ();
  MemPtrFree((MemPtr)gValues);
  PrefSetAppPreferences(APP_CREATOR, PREFS_SPEED, PREFS_VERSION, &gSleep, sizeof(gSleep), false);
}


/***********************************************************************
 * main function
 ***********************************************************************/
UInt32 PilotMain(UInt16 cmd, MemPtr cmdPBP, UInt16 launchFlags){
	UInt16 error;
	error = RomVersionCompatible (MINVERSION, launchFlags);
	if (error) return (error);


  /***
  * NORMAL STARTUP
  ****/
	if ( cmd == sysAppLaunchCmdNormalLaunch ) {
    error = StartApplication ();

    FrmGotoForm(FORM_main);

		AppEventLoop ();
		StopApplication ();
	}
	return 0;
}
