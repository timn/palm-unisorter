/* $Id: countsort.c,v 1.1.1.1 2003/02/10 23:15:15 tim Exp $
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
 * CountSort (Distribution Counting)
 * Ideas from lecture of L. Kobbelt, Implementation tricks from
 * R. Sedgewick, Algorithms in C.
 * Using marker elements v[0] = -1 and v[VALUES_NUM+1]=max(v[i])+1
 * and v[i] > 0 for all i>0 from N
 *
 * Known issue: It looks REALLY bad... I mean visualization for this is just nuts..
 */

#include "UniSorter.h"
#include "gadget.h"

void countsort(Int8 *values) {
  UInt8 i, j, count[VALUES_MAX];
  Int8 *b;

  b = (Int8 *)MemPtrNew(MemPtrSize(values));

  for (j=0; j < VALUES_MAX; j++)  count[j] = 0;
  for (i=1; i <= VALUES_NUM; i++)  count[values[i]] += 1;
  for (j=1; j < VALUES_MAX; j++)  count[j] = count[j-1]+count[j];

  for (i = VALUES_NUM; i >= VALUES_START; i--)  b[count[values[i]]--] = values[i];

  for (i = 1; i <= VALUES_NUM; i++) {
    Sleep();
    GadgetEraseDot(i);
    values[i] = b[i];
    GadgetDrawDot(i);
  }

  MemPtrFree((MemPtr)b);

}
