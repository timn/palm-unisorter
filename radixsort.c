/* $Id: radixsort.c,v 1.1 2003/02/10 23:15:15 tim Exp $
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
 * RadixSort (Straight)
 * Ideas from lecture of L. Kobbelt, Implementation tricks from
 * R. Sedgewick, Algorithms in C.
 * Using marker elements v[0] = -1 and v[VALUES_NUM+1]=max(v[i])+1
 * and v[i] > 0 for all i>0 from N
 *
 * Note: We use Int8 for the values, but only for our marker element
 * values[0] == -1. Our "real" values are all 0 <= value[i] < VALUES_MAX
 * for all 0 < i <= VALUES_NUM.
 */

#include "UniSorter.h"
#include "gadget.h"

#define RSm 1
#define RSM 2
#define RSW 7

static UInt8 bits (Int8 value, UInt8 k, UInt8 j) {
  return ((UInt8)value >> k) & ~(~0 << j);
}

void radixsort(Int8 *values) {
  UInt8 i, j, pass, count[RSM];
  Int8 *b;

  b = (Int8 *)MemPtrNew(MemPtrSize(values));

  for (pass=0; pass < (RSW/RSm)+1; pass++) {
    for (j=0; j < RSM; j++)  count[j] = 0;
    for (i=1; i <= VALUES_NUM; i++)  count[bits(values[i], pass * RSm, RSm)] += 1;
    for (j=1; j < RSM; j++)  count[j] = count[j-1] + count[j];
    for (i=VALUES_NUM; i >= VALUES_START; i--)  b[count[bits(values[i], pass*RSm, RSm)]--] = values[i];
    for (i=1; i <= VALUES_NUM; i++) {
      GadgetEraseDot(i);
      values[i] = b[i];
      GadgetDrawDot(i);
    }
    Sleep();
  }

  MemPtrFree((MemPtr)b);
}
