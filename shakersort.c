/* $Id: shakersort.c,v 1.1 2003/02/10 23:15:15 tim Exp $
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
 * Created 2002/08/10
 *
 *
 * ShakerSort (Thanx to Tob Weyand, who uses BadTabs(TM) and Windoze ;-)
 * Ideas from lecture of L. Kobbelt, Implementation tricks from
 * R. Sedgewick, Algorithms in C.
 * Using marker elements v[0] = -1 and v[VALUES_NUM+1]=max(v[i])+1
 * and v[i] > 0 for all i>0 from N
 */

#include "UniSorter.h"
#include "gadget.h"

void shakersort(Int8 *values) {
  UInt8 l, r, i, k;
  l = 1;
  r = VALUES_NUM;

  /* If the array is already sorted, k will not be changed and the
   * algorithm will terminate after the first pass.
   */
  k = 0;

  do {
    for( i=l; i<=r; i++ ) {
      if ( values[i-1] > values[i] ) {
			  GadgetSwap(i, i-1);
			  k = i;
      }
    }
    r = k-1;

    Sleep();

    for( i=r; i>=l; i-- ) {
      if ( values[i-1]>values[i] ) {
        GadgetSwap(i, i-1);
        k = i;
      }
    }
    l = k+1;

    Sleep();
	
  } while ( l <= r );
}
