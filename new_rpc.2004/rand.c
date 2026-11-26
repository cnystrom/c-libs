/*
 *    rand.c
 *
 *    Copyright (C) 2003  <Chris Nystrom>
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *    Contact Author at:
 *
 *    Chris Nystrom
 *    CHANGEME
 *    CHANGEME
 *
 *    E-Mail: CHANGEME, CHANGEME,
 *              or CHANGEME
 *
 *    Soli Deo Gloria
 *
 */

#include "rand.h"

/* Seed the randomizer with the timer */
void
randomize(void)
{
  time_t timer;
  srand ((unsigned) time (&timer));
}
 
/* Returns an integer from 1 to i */
int
rand_int(int i)
{
  if (i <= 0)
  {
#ifdef DEBUG
    printf("Error: rand_int i <= 0.\n");
#endif
    return(-1);
  }
  else
    return(1 + (int) (i * (rand() / (RAND_MAX + 1.0))));
}

double
rand_double(void)
{
  return((float) rand());
}

double
rand_0to1(void)
{
  return((float) rand() / (float) 0x7fffffff);
}

