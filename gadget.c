/* $Id: gadget.c,v 1.1 2003/02/10 23:15:15 tim Exp $
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

#include "gadget.h"
#include "color.h"


/** WARNING
 * Originally I made checks in every function if at least gForm was set,
 * but since this app wants to implement sorting algorithms in a fast an
 * efficient way I have removed all those checks. Make sure, that all
 * global have been set (see GadgetSet below) before you call any
 * Gadget* Function besides GadgetSet!
 */

FormPtr gForm=NULL;
UInt16 gGadgetID=0, gGadgetIndex=0;
Int8 *gGadgetValues=NULL;
RectangleType gGadgetBounds;
RGBColorType gGadgetRed={0x00, 0xFF, 0x00, 0x00};

/*****************************************************************************
* Function: GadgetDraw
*
* Description: Draws the basic gadget (grid, days, times)
*****************************************************************************/
void GadgetDraw(void) {
  RectangleType rect;
  UInt8 i;
  RGBColorType color, prevColor;

  // Erase background
  WinEraseRectangle(&gGadgetBounds, 0);

  // Draw Grid: Color is light gray
  color.r = 0x77;  color.g = 0x77;  color.b = 0x77;

  TNSetForeColorRGB(&color, &prevColor);

  RctSetRectangle(&rect, gGadgetBounds.topLeft.x, gGadgetBounds.topLeft.y,
                         gGadgetBounds.extent.x, gGadgetBounds.extent.y);
  WinDrawRectangleFrame(simpleFrame, &rect);

  TNSetForeColorRGB(&prevColor, NULL);

  for(i=VALUES_START; i <= VALUES_NUM; ++i) GadgetDrawDot(i);

}

/*****************************************************************************
* Function: GadgetHandler
*
* Description: We use extended Gadgeting => We need an event handler for it
*****************************************************************************/
Boolean GadgetHandler(FormGadgetTypeInCallback *gadgetP, UInt16 cmd, void *paramP) {
  Boolean handled = false; 
  EventType *event = (EventType *)paramP;
  
  switch (cmd) { 
    case formGadgetDrawCmd: 
      //Sent to active gadgets any time form is  
      //drawn or redrawn. 
      GadgetDraw();
      gadgetP->attr.visible = true; 
      handled = true; 
      break; 
       
    case formGadgetHandleEventCmd: 
      //Sent when form receives a gadget event.  
      //paramP points to EventType structure.

      if (event->eType == frmGadgetEnterEvent) { 
        // penDown in gadget's bounds.
        // GadgetTap((FormGadgetType *)gadgetP, event);
        handled = true;
      }
      if (event->eType == frmGadgetMiscEvent) {
        //This event is sent by your application
        //when it needs to send info to the gadget
      }
      break;

    case formGadgetDeleteCmd:
      //Perform any cleanup prior to deletion.
      break;

    case formGadgetEraseCmd:
      //FrmHideObject takes care of this if you 
      //return false.
       handled = false;
       break;

    default:
      break;

  }
  return handled;
}

void GadgetFillRandom(void) {
  UInt8 i, j, k;
  Int8 t;

  // Set Marker/Sentinel
  gGadgetValues[0] = -1;

  // Initialize
  for(i=VALUES_START; i <= VALUES_NUM + 1; ++i)  gGadgetValues[i] = i-1; // -1 because of marker element
  // Fill to VALUES_NUM +1 (+1 is "strange") to have a top sentinel, needed for quicksort_rect!

  // Permute
  for(i=0; i < VALUES_NUMPERMUTES; ++i) {
    for (j=VALUES_START; j <= VALUES_NUM; ++j) {
      k = (SysRandom(0) % (VALUES_NUM - 1)) + 1;

      t = gGadgetValues[j];
      gGadgetValues[j] = gGadgetValues[k];
      gGadgetValues[k] = t;
    }
  }

  GadgetDraw();

}

void GadgetDrawDot(UInt8 x) {
  WinDrawPixel(gGadgetBounds.topLeft.x+x-1, gGadgetBounds.topLeft.y + VALUES_MAX - gGadgetValues[x] -1);
}

void GadgetEraseDot(UInt8 x) {
  WinErasePixel(gGadgetBounds.topLeft.x+x-1, gGadgetBounds.topLeft.y + VALUES_MAX - gGadgetValues[x] -1);
}


/*****************************************************************************
* Function: GadgetSet
*
* Description: Must be called before draw to set the form the gadget is in
*              and the IDs of the Gadget and the hint gadget
*****************************************************************************/
void GadgetSet(FormPtr frm, UInt16 gadgetID) {
  gForm=frm;
  gGadgetID=gadgetID;
  gGadgetIndex=FrmGetObjectIndex(gForm, gGadgetID);
  gGadgetValues = FrmGetGadgetData(gForm, gGadgetIndex);
  FrmGetObjectBounds(gForm, gGadgetIndex, &gGadgetBounds);
}

void GadgetSwap(UInt8 i, UInt8 j) {
  Int8 t;

  // -1 in all draw routines for x because of marker element, for y to fit in frame
  WinErasePixel(gGadgetBounds.topLeft.x+i-1, gGadgetBounds.topLeft.y+ VALUES_MAX - gGadgetValues[i] - 1);
  WinErasePixel(gGadgetBounds.topLeft.x+j-1, gGadgetBounds.topLeft.y+ VALUES_MAX - gGadgetValues[j] - 1);

  t = gGadgetValues[i];
  gGadgetValues[i] = gGadgetValues[j];
  gGadgetValues[j] = t;

  WinDrawPixel(gGadgetBounds.topLeft.x+i-1, gGadgetBounds.topLeft.y + VALUES_MAX - gGadgetValues[i] - 1);
  WinDrawPixel(gGadgetBounds.topLeft.x+j-1, gGadgetBounds.topLeft.y + VALUES_MAX - gGadgetValues[j] - 1);

}



/*****************************************************************************
* Function: GadgetDrawRect
*
* Description: Draws a rectangle in the graph area. Give it graph-relative,
*              not gadget-absolute values, that is done here automatically
*****************************************************************************/
void GadgetDrawRect(UInt8 x, UInt8 y, Int8 width, Int8 height) {
  RectangleType tmp;
  RGBColorType prevColor;

  RctSetRectangle(&tmp, gGadgetBounds.topLeft.x + x - 1,
                        gGadgetBounds.topLeft.y + + VALUES_MAX - y,
                        width, height);

  TNSetForeColorRGB(&gGadgetRed, &prevColor);
  WinDrawRectangleFrame(simpleFrame, &tmp);
  TNSetForeColorRGB(&prevColor, NULL);

}
