/**
 * Nina's Diary
 *
 * Author: Thomas Cherryhomes
 *  <thom.cherryhomes@gmail.com>
 *
 * Get/Put # of entries.
 */

#include <atari.h>
#include <6502.h>
#include "num_entries.h"

extern unsigned char buf[128];

/**
 * Get number of entries available on disk
 */
unsigned char num_entries_get(void)
{
  struct regs r;
  
  OS.dcb.ddevic=0x30; // Disk drive
  OS.dcb.dunit=1;
  OS.dcb.dcomnd='R'; // Read
  OS.dcb.dtimlo=0x0F; // Default timeout
  OS.dcb.dstats=0x40; // Read
  OS.dcb.daux=1;     // Get first sector
  OS.dcb.dbuf=&buf;  // Point to sector buffer
  OS.dcb.dbyt=128;
  r.pc=0xE453;
  _sys(&r);
  
  return buf[127];
}

/**
 * Put entries back onto disk (use num_entries_get_first!) 
 */
void num_entries_put(unsigned char num_entries)
{
  struct regs r;

  buf[127]=num_entries;
  OS.dcb.ddevic=0x30; // Disk drive
  OS.dcb.dunit=1;
  OS.dcb.dcomnd='W'; // Read
  OS.dcb.dtimlo=0x0F; // Default timeout
  OS.dcb.dstats=0x80; // Read
  OS.dcb.daux=1;     // Get first sector
  OS.dcb.dbuf=&buf;  // Point to sector buffer
  r.pc=0xE453;
  _sys(&r);
}
