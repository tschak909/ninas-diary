/**
 * Routine to call SIO to format a very blank disk
 */

#include <atari.h>
#include <_atarios.h>
#include <6502.h>
#include "format.h"

extern unsigned char buf[128];

void format_disk(unsigned char drive_num)
{
  struct regs r;
  
  OS.dcb.ddevic=0x30;
  OS.dcb.dunit=drive_num;
  OS.dcb.dcomnd=0x22; // Format
  OS.dcb.dbuf=&buf;
  OS.dcb.dtimlo=0xFE;
  OS.dcb.dstats=0x40; // command will return something
  r.pc=0xE453; // DSKINV
  _sys(&r);
}
