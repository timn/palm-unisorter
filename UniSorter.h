/* $Id: UniSorter.h,v 1.1 2003/02/10 23:15:15 tim Exp $
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
 *
 *
 * Definitions:
 * 1:         Version
 * 100-199:   app specific values
 * 1001-1999: Forms, form items
 * 2001-2999: Menus and menu items
 * 4001-4999: Help
 * 8001-8999: Special stuff, bitmaps etc.
 */

#ifndef __UNISORTER_H_
#define __UNISORTER_H_

// define DEBUG

#include <PalmOS.h>

#define APP_CREATOR 'USRT'
#define APP_ID 100
#define APP_NAMEID 101
#define APP_CATEGORIES 102
// Apps needing B/W should use 1, grayscale apps use 4 (16 grays)
#define APP_COLORDEPTH 4

#define MINVERSION		0x03500000

#define PREFS_VERSION 1
#define PREFS_SPEED 1



// Number of values, max is 255, but since palm's display is only 160 wide...
#define VALUES_NUM 125
// Do NEVER set this > 127 or strange things WILL occur
// because we only have Int8 datatype. If you change that everywhere
// go on and set... You have been warned
#define VALUES_MAX 125
// This is 1 because 0 is our marker element (= -1),
// see Algorithms, Sedgewick about InsertionSort, QuickSort
#define VALUES_START 1
// Number of permutations to do to randomize data, the whole array will
// be permuted NUMPERMUTES often!
#define VALUES_NUMPERMUTES 3


#define FORM_main 1001
#define GADGET_main 1002
#define BUTTON_run 1003
#define BUTTON_reset 1004
#define BUTTON_break 1005
#define GROUP_algo 5
#define BUTTON_speed 1006
#define BUTTON_help 1007
#define HELP_main 1008
#define BUTTON_info 1009

// This value is used to disable the controls while sorting
#define ALGOS_NUM 12
#define ALGOS_FIRST 1011
#define BUTTON_quick 1011
#define BUTTON_insert 1012
#define BUTTON_select 1013
#define BUTTON_bubble 1014
#define BUTTON_shell 1015
#define BUTTON_merge 1016
#define BUTTON_quickm 1017
#define BUTTON_quickr 1018
#define BUTTON_heap 1019
#define BUTTON_shaker 1020
#define BUTTON_radix 1021
#define BUTTON_count 1022

#define FORM_speed 1030
#define SLIDER_speed 1031
#define BUTTON_speed_ok 1032
#define BUTTON_speed_cancel 1033


#define FORM_about 1060
#define BITMAP_logo 1061
#define BUTTON_about_ok 1062


#define MENU_main 2001
#define MENUITEM_about 2002

#define ALERT_ROMIncompatible 4001
#define ALERT_debug 4002
#define ALERT_nomem 4004
#define ALERT_sorted 4005

#define BITMAP_run 5001
#define BITMAP_run_clicked 5002
#define BITMAP_reset 5003
#define BITMAP_reset_clicked 5004
#define BITMAP_help 5005
#define BITMAP_help_clicked 5006
#define BITMAP_info 5007
#define BITMAP_info_clicked 5008

#define HelpROMIncompatible 1005

extern Boolean HandleMenuEvent (UInt16 command);
extern void *GetObjectPtr(UInt16 objectID);
extern void Sleep(void);

#endif /* __UNISORTER_H_ */
