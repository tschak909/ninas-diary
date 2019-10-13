/**
 * Routine to call SIO to format a very blank disk
 */

#include <atari.h>
#include <_atarios.h>
#include <6502.h>
#include "format.h"
#include "config.h"

extern unsigned char buf[SECTOR_SIZE];

void format_disk(unsigned char drive_num)
{
  struct regs r;

  OS.dsctln=SECTOR_SIZE;
#ifdef PERCOM_CONFIG
  buf[0]=PERCOM_TRACKS;
  buf[1]=3; // assume step rate of 3
  buf[2]=0;
  buf[3]=PERCOM_SPT;
  buf[4]=PERCOM_SIDES;
  buf[5]=PERCOM_DENSITY;
  buf[6]=PERCOM_SECTORH;
  buf[7]=PERCOM_SECTORL;
  buf[8]=1; // assume drive is present.
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
#endif
  
  OS.dcb.ddevic=0x31;
  OS.dcb.dunit=drive_num;
  OS.dcb.dcomnd=FORMAT_COMMAND; // Format
  OS.dcb.dbuf=&buf;
  OS.dcb.dtimlo=0xFE;
  OS.dcb.dstats=0x40; // command will return something
  
  r.pc=0xE453; // DSKINV
  _sys(&r);
}
