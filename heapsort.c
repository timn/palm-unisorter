/* $Id: heapsort.c,v 1.1.1.1 2003/02/10 23:15:15 tim Exp $
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
 * HeapSort
 * Ideas from lecture of L. Kobbelt, Implementation tricks from
 * R. Sedgewick, Algorithms in C.
 * Using marker elements v[0] = -1 and v[VALUES_NUM+1]=max(v[i])+1
 * and v[i] > 0 for all i>0 from N
 */

#include "UniSorter.h"
#include "gadget.h"

#define HEAP_BUILDDELAY 20

static void downheap(Int8 *values, UInt8 N, UInt8 k) {
  UInt8 j;
  Int8 v;

  v = values[k];
  while (k <= (N / 2)) {
    j = k+k;
    if ((j < N) && (values[j] < values[j+1])) j++;
    if (v >= values[j]) break;
    GadgetEraseDot(k);
    values[k] = values[j];
    GadgetDrawDot(k);
    k = j;
  }
  GadgetEraseDot(k);
  values[k] = v;
  GadgetDrawDot(k);
}

void heapsort(Int8 *values) {
  UInt8 i;

  // Build the heap, have a delay every HEAP_BUILDDELAY elements
  for (i = (UInt8)(VALUES_NUM/2); i >= VALUES_START; --i) {
    downheap(values, VALUES_NUM, i);
    if ((i % HEAP_BUILDDELAY) == 0)  Sleep();
  }

  // Show the user what we have done :-)
  Sleep(); Sleep();


  i = VALUES_NUM;
  while(i > VALUES_START) {
    GadgetSwap(VALUES_START, i);
    downheap(values, --i, VALUES_START);
    Sleep();
  }

}
