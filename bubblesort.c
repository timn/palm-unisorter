/* $Id: bubblesort.c,v 1.1 2003/02/10 23:15:15 tim Exp $
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
 * BubbleSort
 * Ideas from lecture of L. Kobbelt, Implementation tricks from
 * R. Sedgewick, Algorithms in C.
 * Using marker element v[0] = -1 and v[i] > 0 for all i>0 from N
 */

#include "UniSorter.h"
#include "gadget.h"




void bubblesort(Int8 *values) {
  UInt8 i, j;

  for(i=VALUES_NUM; i >= VALUES_START; --i) {
    for (j=2; j <= i; ++j)
      if (values[j-1] > values[j])
        GadgetSwap(j, j-1);

    Sleep();
  }
}
