/* $Id: shellsort.c,v 1.1.1.1 2003/02/10 23:15:15 tim Exp $
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
 * ShellSort
 * Ideas from lecture of L. Kobbelt, Implementation tricks from
 * R. Sedgewick, Algorithms in C.
 * Using marker elements v[0] = -1 and v[VALUES_NUM+1]=max(v[i])+1
 * and v[i] > 0 for all i>0 from N
 */

#include "UniSorter.h"
#include "gadget.h"


void shellsort(Int8 *values) {
  UInt8 i, j, h;
  Int8 v;

  for (h = 1; h <= (UInt8)(VALUES_NUM / 9); h = 3*h+1); 
  for (; h > 0; h /= 3) {
    for(i=h+1; i <= VALUES_NUM; ++i) {
      GadgetEraseDot(i);
      v = values[i];
      j = i;
      while ((j > h) && (values[j-h] > v)) {
        GadgetEraseDot(j);
        values[j] = values[j-h];
        GadgetDrawDot(j);
        j -= h;
      }
      GadgetEraseDot(j);
      values[j] = v;
      GadgetDrawDot(j);
    }
    Sleep();
  }
}
