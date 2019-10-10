/**
 * Nina's Diary
 *
 * Author: Thomas Cherryhomes
 *  <thom.cherryhomes@gmail.com>
 *
 * Disk blanking routine
 */

#ifndef BLANK_H
#define BLANK_H

#include <6502.h>
#include <atari.h>
#include <_atarios.h>
#include <string.h>
#include "bootsect.h"

void blank_write(unsigned char drive_num);

#endif /* BLANK_H */
