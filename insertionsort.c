/* $Id: insertionsort.c,v 1.1.1.1 2003/02/10 23:15:15 tim Exp $
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
 * InsertionSort
 * Ideas from lecture of L. Kobbelt, Implementation tricks from
 * R. Sedgewick, Algorithms in C.
 * Using marker elements v[0] = -1 and v[VALUES_NUM+1]=max(v[i])+1
 * and v[i] > 0 for all i>0 from N
 *
 * Known issue: We could do the insert faster by searching for the
 *              insertion place with a binary search, but we would
 *              need a dynamic data structure to allow insertions
 *              without moving around all following data.
 */

#include "UniSorter.h"
#include "gadget.h"


void insertionsort(Int8 *values) {
  UInt8 i, j;
  Int8 v;

  for(i=2; i <= VALUES_NUM; ++i) {
    Sleep();
    v = values[i];
    GadgetEraseDot(i);
    j = i;
    while (values[j-1] > v) {
      // GadgetSwap(j, j-1);
      GadgetEraseDot(j);
      values[j] = values[j-1];
      GadgetDrawDot(j);
      j -= 1;
    }
    GadgetEraseDot(j);
    values[j] = v;
    GadgetDrawDot(j);
  }

}
