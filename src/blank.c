/**
 * Nina's Diary
 *
 * Author: Thomas Cherryhomes
 *  <thom.cherryhomes@gmail.com>
 *
 * Disk blanking routine
 */

#include <6502.h>
#include <atari.h>
#include <string.h>
#include "bootsect.h"

extern unsigned char buf[256];

void blank_write(unsigned char drive_num)
{
  struct regs r;
  unsigned short i;
  
  // nice blank sector
  memset(&buf,0,sizeof(buf));
  
  // Write blank sectors to disk
  OS.dcb.ddevic=0x31; // Disk drive
  OS.dcb.dunit=drive_num;
  OS.dcb.dcomnd='P'; // Write, no verify
  OS.dcb.dtimlo=0x0F; // Default timeout
  OS.dcb.dstats=0x80; // Write
  
  for (i=4;i<720;i++)
    {
      OS.dcb.daux=i;
      OS.dcb.dbuf=&buf;
      OS.dsctln=256;
      r.pc=0xE453;
      _sys(&r);
    }
}
