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

extern unsigned char buf[128];

void blank_write(unsigned char drive_num)
{
  struct regs r;
  unsigned short i;
  
  // nice blank sector
  memset(&buf,0,sizeof(buf));
  
  // Write boot sectors to disk
  OS.dcb.ddevic=0x31; // Disk drive
  OS.dcb.dunit=drive_num;
  OS.dcb.dcomnd='P'; // Write, no verify
  OS.dcb.dtimlo=0x0F; // Default timeout
  OS.dcb.dstats=0x80; // Write
  OS.dcb.dbyt=128;
  
  for (i=2;i<1040;i++)
    {
      OS.dcb.daux=i;
      OS.dcb.dbuf=&buf;
      r.pc=0xE453;
      _sys(&r);
    }
}
