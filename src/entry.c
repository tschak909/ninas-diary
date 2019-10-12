/**
 * Nina's Diary
 *
 * Author: Thomas Cherryhomes
 *  <thom.cherryhomes@gmail.com>
 *
 * Get/Put an entry
 */

#include <6502.h>
#include <atari.h>
#include "entry.h"

extern unsigned char* video_ptr;

/**
 * Read an entry
 */
void entry_read(unsigned char entry)
{
  struct regs r;
  unsigned char i;
  unsigned short start_sector;

  start_sector=(entry<<3)+1;
  OS.dcb.ddevic=0x30; // Disk drive
  OS.dcb.dunit=1;
  OS.dcb.dcomnd='R'; // Read
  OS.dcb.dtimlo=0x0F; // Default timeout
  OS.dcb.dstats=0x40; // Read
  OS.dcb.dbyt=128;
  
  for (i=0;i<8;i++)
    {
      OS.dcb.daux=start_sector+i;     // Get first sector
      OS.dcb.dbuf=&video_ptr[i<<7];  // Point to sector buffer
      r.pc=0xE453;
      _sys(&r);
    }
}

/**
 * Write an entry
 */
void entry_write(unsigned char entry)
{
  struct regs r;
  unsigned char i;
  unsigned short start_sector;

  start_sector=(entry<<3)+1;
  OS.dcb.ddevic=0x30; // Disk drive
  OS.dcb.dunit=1;
  OS.dcb.dcomnd='W'; // Write
  OS.dcb.dtimlo=0x0F; // Default timeout
  OS.dcb.dstats=0x80; // Write
  OS.dcb.dbyt=128;
  
  for (i=0;i<8;i++)
    {
      OS.dcb.daux=start_sector+i;     // Get first sector
      OS.dcb.dbuf=&video_ptr[i<<7];  // Point to sector buffer
      r.pc=0xE453;
      _sys(&r);
    }
}
