/* $Id: mergesort.c,v 1.1.1.1 2003/02/10 23:15:15 tim Exp $
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
 * MergeSort
 * Ideas from lecture of L. Kobbelt, Implementation tricks from
 * R. Sedgewick, Algorithms in C.
 * Using marker elements v[0] = -1 and v[VALUES_NUM+1]=max(v[i])+1
 * and v[i] > 0 for all i>0 from N
 */

#include "UniSorter.h"
#include "gadget.h"

Int8 *gMergeHelp;


static void msort(Int8 *values, UInt8 l, UInt8 r) {
  if (r > l) {
    UInt8 i, j, m, k;

    m = (UInt8)((r+l)/2);
    msort(values, l, m);
    msort(values, m+1, r);
    for (i = m+1; i > l; --i) gMergeHelp[i-1] = values[i-1];
    for (j=m; j < r; ++j)  gMergeHelp[r+m-j] = values[j+1];
    for (k=l; k <= r; ++k) {
      GadgetEraseDot(k);
      values[k] = (gMergeHelp[i] < gMergeHelp[j]) ? gMergeHelp[i++] : gMergeHelp[j--];
      GadgetDrawDot(k);
    }
    Sleep();
  }
}

void mergesort(Int8 *values) {
  gMergeHelp=(Int8 *)MemPtrNew(MemPtrSize(values));
  msort(values, 1, VALUES_NUM);
  MemPtrFree((MemPtr)gMergeHelp);
}
