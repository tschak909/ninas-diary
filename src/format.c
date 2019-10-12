/**
 * Routine to call SIO to format a very blank disk
 */

#include <atari.h>
#include <_atarios.h>
#include <6502.h>
#include "format.h"

extern unsigned char buf[256];

void format_disk(unsigned char drive_num)
{
  struct regs r;

  OS.dsctln=256;

  buf[0]=40;
  buf[1]=3;
  buf[2]=0;
  buf[3]=18;
  buf[4]=0;
  buf[5]=4;
  buf[6]=1;
  buf[7]=0;
  buf[8]=1;
  buf[9]=0;
  buf[10]=0;
  buf[11]=0;
  
  OS.dcb.ddevic=0x31;
  OS.dcb.dunit=drive_num;
  OS.dcb.dcomnd='O';
  OS.dcb.dbuf=&buf;
  OS.dcb.dtimlo=0x0F;
  OS.dcb.dstats=0x80;
  OS.dcb.dbyt=12;
  
  r.pc=0xE459;
  _sys(&r);
  
  OS.dcb.ddevic=0x31;
  OS.dcb.dunit=drive_num;
  OS.dcb.dcomnd=0x21; // Format
  OS.dcb.dbuf=&buf;
  OS.dcb.dtimlo=0xFE;
  OS.dcb.dstats=0x40; // command will return something
  
  r.pc=0xE453; // DSKINV
  _sys(&r);
}
