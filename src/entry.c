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
  
  start_sector=(entry<<2)+1;
  OS.dcb.ddevic=0x31; // Disk drive
  OS.dcb.dunit=1;
  OS.dcb.dcomnd='R'; // Read
  OS.dcb.dtimlo=0x0F; // Default timeout
  OS.dcb.dstats=0x40; // Read
  
  for (i=0;i<4;i++)
    {
      OS.dcb.daux=start_sector+i;     // Get first sector
      OS.dcb.dbuf=&video_ptr[i<<8];  // Point to sector buffer
      OS.dsctln=256;
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
  
  start_sector=(entry<<2)+1;
  OS.dcb.ddevic=0x31; // Disk drive
  OS.dcb.dunit=1;
  OS.dcb.dcomnd='P'; // Write
  OS.dcb.dtimlo=0x0F; // Default timeout
  OS.dcb.dstats=0x80; // Write
  
  for (i=0;i<4;i++)
    {
      OS.dcb.daux=start_sector+i;     // Get first sector
      OS.dcb.dbuf=&video_ptr[i<<8];  // Point to sector buffer
      OS.dsctln=256;
      r.pc=0xE453;
      _sys(&r);
    }
}
