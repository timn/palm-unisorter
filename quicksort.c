/* $Id: quicksort.c,v 1.1 2003/02/10 23:15:15 tim Exp $
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
 * BubbleSort
 * Ideas from lecture of L. Kobbelt, Implementation tricks from
 * R. Sedgewick, Algorithms in C.
 * Using marker elements v[0] = -1 and v[VALUES_NUM+1]=max(v[i])+1
 * and v[i] > 0 for all i>0 from N
 *
 * Known issue: Will overflow the stack if called on an already sorted
 *              field. Palm's stack too small, no time to implement
 *              iterative variant. Since only done for my own understanding
 *              it's not really worth it...
 *              The Median version should make it, I didn't test it though
 */

#include "UniSorter.h"
#include "gadget.h"


static void qsort(Int8 *values, UInt8 l, UInt8 r) {
  if (l < r) {
    UInt8 i=l-1, j=r;

    /** Partition code */
    for(;;) {

      while (values[++i] < values[r]);
      while (values[--j] > values[r]);

      if (i >= j) break;

      GadgetSwap(i, j);
    }
    /** End of partition code */

    GadgetSwap(i, r);
    Sleep();
    qsort(values, l, i-1);
    qsort(values, i+1, r);
  }
}

void quicksort(Int8 *values) {
  qsort(values, 1, VALUES_NUM);
}



/** QuickSort with Median-of-three */

static UInt8 median(Int8 *values, UInt8 x, UInt8 y, UInt8 z) {
  if (values[z] > values[y]) {
    if (values[y] > values[x]) {
      return x;
    } else {
      return (values[z] > values[x]) ? x : z;
    }
  } else {
    if (values[z] > values[x]) {
      return z;
    } else {
      return (values[y] > values[x]) ? x : y;
    }
  }
}


static void qsortm(Int8 *values, UInt8 l, UInt8 r) {
  if (l < r) {
    UInt8 i=l-1, j=r;

    // Put a good comparison element at last position
    // We call median by function, coule be implemented here to save some
    // time (no stack operations etc.). Should be fast enough for this
    // simple learning though...
    GadgetSwap(r, median(values, l, r, (UInt8)((l+r)/2)));

    /** Partition code */
    for(;;) {
      
      while (values[++i] < values[r]);
      while (values[--j] > values[r]);

      if (i >= j) break;

      GadgetSwap(i, j);
    }
    /** End of partition code */

    GadgetSwap(i, r);
    Sleep();
    qsortm(values, l, i-1);
    qsortm(values, i+1, r);
  }
}


void quicksort_median(Int8 *values) {
  qsortm(values, 1, VALUES_NUM);
}



/** This is the median implementation from above
 * it is very slow though since it has a lot of extra drawing
 * to make the partitioning visible...
 */

static void qsortr(Int8 *values, UInt8 l, UInt8 r) {
  if (l < r) {
    UInt8 i=l-1, j=r;

    GadgetSwap(r, median(values, l, r, (UInt8)((l+r)/2)));

    /** Partition code */
    for(;;) {
      
      while (values[++i] < values[r]);
      while (values[--j] > values[r]);

      if (i >= j) break;

      GadgetSwap(i, j);
    }
    /** End of partition code */

    GadgetSwap(i, r);

    /* i is guareanteed to be in final position, now we draw the rectangles, the following
     * "picture may help to understand
     *
     *            i+1    r
     *              -----/  <--------value[r+1]-1 (Guaranteed to exist, sentinels!) Otherwise sorted
     *             |   / |                         in calling function
     *             | /   |
     *             /   A |
     *           i  -----  <------ value[i]+1
     *    -----/  <------------- value[i]-1
     *    |  / |
     *    |/   |
     *   /   B |
     * /  -----  <-------- value[l-1]+1 (Also guaranteed to exist)
     *   l    i-1
     *
     *
     *  X-Position of A:       i+1
     *  Y-Position of A:       values[r+1]-1
     *  Width of partition A:  r-(i+1) = r-i-1;
     *  Height of partition A: value[r+1]-1-(value[i]+1)=value[r+1]-value[i]-2
     *
     *  X-Position of B:       l
     *  Y-Position of B:       value[i]-1
     *  Width of partition B:  i-1-l
     *  Height of partition A: value[i]-1-(value[l-1]+1)=value[i]-value[l-1]-2
     */
 
    GadgetDraw();

    // Draw partition A
    GadgetDrawRect(i+1, values[r+1]-1, (r-i-1), (values[r+1]-values[i]-2));

    // Draw partition B
    GadgetDrawRect(l, values[i]-1, (i-1-l), (values[i]-values[l-1]-2));
 
    Sleep();
    qsortr(values, l, i-1);
    qsortr(values, i+1, r);
  }
}


void quicksort_rect(Int8 *values) {
  qsortr(values, 1, VALUES_NUM);
  // We need to draw again to erase the last painted rectangles
  GadgetDraw();
}



