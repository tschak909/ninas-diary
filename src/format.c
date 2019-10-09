/**
 * Routine to call SIO to format a very blank disk
 */

#include <atari.h>
#include <_atarios.h>
#include <stdlib.h>
#include <6502.h>
#include "format.h"

void format_disk(unsigned char drive_num)
{
  struct regs r;
  
  OS.dcb.ddevic=0x30;
  OS.dcb.dunit=drive_num;
  OS.dcb.dcomnd=0x21; // Format
  OS.dcb.dbuf=malloc(256);
  OS.dcb.dtimlo=0xFE;
  OS.dcb.dstats=0x40; // command will return something
  r.pc=0xE453; // DSKINV
  _sys(&r);
  free(OS.dcb.dbuf);
}
