/**
 * Nina's Diary
 *
 * Author: Thomas Cherryhomes
 *  <thom.cherryhomes@gmail.com>
 *
 * User Interface Routines
 */

#include <atari.h>
#include <peekpoke.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include "ui.h"
#include "charset.h"
#include "format.h"
#include "bootsect.h"
#include "num_entries.h"
#include "entry.h"
#include "blank.h"
#include "unicorn.h"
#include "config.h"

#define DISPLAY_LIST 0x0600
#define DISPLAY_MEMORY 0x3C00

#define P712 84    // Background
#define P708 170   // title/horse highlights 
#define P709 15    // mode 2 text intensity
#define P710 84    // mode 2 text background


unsigned char* video_ptr;
static unsigned char* dlist_ptr;
static unsigned short screen_memory;
static unsigned char tcx,cx,cy,ox,oy;
static unsigned char k;
static unsigned char atari_key;

extern unsigned char running;

void dlist_title=
  {
   DL_BLK8,
   DL_BLK8,
   DL_BLK8,
   DL_LMS(DL_CHR20x8x2),
   DISPLAY_MEMORY,
   DL_CHR20x8x2,
   DL_CHR40x8x1,
   DL_CHR40x8x1,
   DL_CHR40x8x1,
   DL_CHR40x8x1,
   DL_CHR40x8x1,
   DL_CHR40x8x1,
   DL_CHR40x8x1,
   DL_CHR40x8x1,
   DL_CHR40x8x1,
   DL_CHR40x8x1,
   DL_CHR40x8x1,
   DL_CHR40x8x1,
   DL_CHR40x8x1,
   DL_CHR40x8x1,
   DL_CHR40x8x1,
   DL_LMS(DL_MAP160x2x4),
   unicorn,
   DL_MAP160x2x4,
   DL_MAP160x2x4,
   DL_MAP160x2x4,
   DL_MAP160x2x4,
   DL_MAP160x2x4,
   DL_MAP160x2x4,
   DL_MAP160x2x4,
   DL_MAP160x2x4,
   DL_MAP160x2x4,
   DL_MAP160x2x4,
   DL_MAP160x2x4,
   DL_MAP160x2x4,
   DL_MAP160x2x4,
   DL_MAP160x2x4,
   DL_MAP160x2x4,
   DL_MAP160x2x4,
   DL_MAP160x2x4,
   DL_MAP160x2x4,
   DL_MAP160x2x4,
   DL_MAP160x2x4,
   DL_MAP160x2x4,
   DL_MAP160x2x4,
   DL_MAP160x2x4,
   DL_MAP160x2x4,
   DL_MAP160x2x4,
   DL_MAP160x2x4,
   DL_MAP160x2x4,
   DL_MAP160x2x4,
   DL_MAP160x2x4,
   DL_JVB,
   0x600
  };

void dlist_entry=
  {
   DL_BLK8,
   DL_BLK8,
   DL_BLK8,
   DL_LMS(DL_CHR20x8x2),
   DISPLAY_MEMORY,

   DL_CHR20x8x2,
   DL_CHR40x8x1,
   DL_CHR40x8x1,
   DL_CHR40x8x1,
   DL_CHR40x8x1,
   DL_CHR40x8x1,
   DL_CHR40x8x1,
   DL_CHR40x8x1,
   DL_CHR40x8x1,
   DL_CHR40x8x1,
   DL_CHR40x8x1,
   DL_CHR40x8x1,
   DL_CHR40x8x1,
   DL_CHR40x8x1,
   DL_CHR40x8x1,
   DL_CHR40x8x1,
   DL_CHR40x8x1,
   DL_CHR40x8x1,
   DL_CHR40x8x1,
   DL_CHR40x8x1,
   DL_CHR40x8x1,
   DL_CHR40x8x1,
   DL_CHR40x8x1,
   
   DL_JVB,
   0x600
  };

#define SetChar(x,y,a) video_ptr[(x)+(y)*40]=(a);
#define GetChar(x,y) video_ptr[(x)+(y)*40]
#define GRAPHICS_0_SCREEN_SIZE (40*25)

void clear_screen()
{
  memset(video_ptr,0,GRAPHICS_0_SCREEN_SIZE);
}

/**
 * Display cursor
 */
void set_cursor(void)
{
  SetChar(cx,cy,GetChar(cx,cy)|0x80);

  if (ox==0xff)
    return;

  SetChar(ox,oy,GetChar(ox,oy)&0x7F);
}

/**
 * Turn cursor off
 */
void set_cursor_off(void)
{
  SetChar(cx,cy,GetChar(cx,cy)&0x7F);
  SetChar(ox,oy,GetChar(ox,oy)&0x7F);
}

/**
 * Print ATASCII string to display memory
 */
void print_string(unsigned char x,unsigned char y,char *s)
{
  do
    {
      if (*s < 32)
	{
	  SetChar(x++,y,*s+64+atari_key);
	}
      else if (*s<96)
	{
	  SetChar(x++,y,*s-32+atari_key);
	}
      else
	{
	  SetChar(x++,y,*s+atari_key);
	}
      ++s;
    } while(*s!=0);
}

/**
 * Set up the display
 */
void ui_setup(void)
{
  POKE(559,0);

  memcpy((void *)DISPLAY_LIST,&dlist_title,sizeof(dlist_title));
  OS.sdlst=(void*)DISPLAY_LIST;
  
  POKE(708,P708);
  POKE(709,P709);
  POKE(710,P710);
  POKE(712,P712);
  dlist_ptr=(unsigned char *)(PEEKW(560));
  screen_memory=PEEKW(560)+4;
  video_ptr=(unsigned char*)(PEEKW(screen_memory));
  charset_use();
  
  POKE(559,34);
}

/**
 * Cursor functions
 */
void set_cursor_left()
{
  if (cx==0)
    cx=39;
  else
    cx--;
}

void set_cursor_right()
{
  if (cx==39)
    cx=0;
  else
    cx++;
}

void set_cursor_up()
{
  if (cy==1)
    {
      cx=20;
    }
  else
    cx=tcx;
    
  if (cy==0)
    cy=19;
  else
    cy--;
}

void set_cursor_down()
{
  if (cy==19)
    {
      cx=20;
      cy=0;
    }
  else
    {
      tcx=cx;
      cy++;
    }
}

void set_cursor_backspace()
{
  if (cx==0)
    {
      cx=39;
      cy--;
    }
  else
    {
      cx--;
    }
  SetChar(ox,oy,0);
}

void set_cursor_return()
{
  cx=0;
  cy++;
}

/**
 * Show/edit entry
 */
void ui_entry(unsigned short e)
{
  unsigned char page[4];
  unsigned short pages_free_int;
  unsigned char pages_free[4];
  unsigned char out[2];
  unsigned char save;
  unsigned char editing_done;

  POKE(559,0);

  memcpy((void *)DISPLAY_LIST,&dlist_entry,sizeof(dlist_entry));
  OS.sdlst=(void*)DISPLAY_LIST;

  dlist_ptr=(unsigned char *)(PEEKW(560));
  screen_memory=PEEKW(560)+4;
  video_ptr=(unsigned char*)(PEEKW(screen_memory));
  
  POKE(559,34);
  
 reload:
  
  itoa(e,page,10);
  clear_screen();
  entry_read(e);
  pages_free_int=TOTAL_PAGES-num_entries_get();
  itoa(pages_free_int,pages_free,10);
  save=0;
  editing_done=0;
  cx=0;
  cy=1;
  ox=0xff;
  oy=0xff;

  set_cursor();
  
  print_string(8,0,"PAGE #");
  print_string(17,0,page);
  print_string(0,20,"\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12");
  print_string(0,21,"\x80\xB3\xA5\xAC\xA5\xA3\xB4\x80 \x1e\x1e page        \x80\xAF\xB0\xB4\xA9\xAF\xAE\x80 \x1f\x1f page");
  print_string(0,22,"\x80\xB3\xB4\xA1\xB2\xB4\x80\x80 save");

  print_string(26,22,pages_free);
  print_string(30,22,"pages free");
  while (PEEK(0xD01F)!=7) {} // Debounce.

  // Editing
  
  while (editing_done==0)
    {
      if (PEEK(0xD01F)==6)
	{
	  save=1;
	  editing_done=1;
	}
      else if (PEEK(0xD01F)==5)
	{
	  editing_done=1;
	  if (e==1)
	    e=1;
	  else
	    e--;
	}
      else if (PEEK(0xD01F)==3)
	{
	  editing_done=1;
	  if (e==TOTAL_PAGES)
	    e=TOTAL_PAGES;
	  else
	    e++;
	}
      else if (kbhit())
	{
	  ox=cx;
	  oy=cy;

	  POKE(OS.atract,0);
	  
	  if (cx>0)
	    tcx=cx;
	  
	  if (PEEK(764)==134)
	    set_cursor_left();
	  else if (PEEK(764)==135)
	    set_cursor_right();
	  else if (PEEK(764)==142)
	    set_cursor_up();
	  else if (PEEK(764)==143)
	    set_cursor_down();
	  else if (PEEK(764)==12)
	    set_cursor_return();
	  else if (PEEK(764)==52)
	    set_cursor_backspace();
	  else if ((PEEK(764)==39) && (atari_key==0))
	    atari_key=128;
	  else if ((PEEK(764)==39) && (atari_key==128))
	    atari_key=0;
	  else
	    {
	      k=cgetc();
	      out[0]=k;
	      print_string(ox,oy,out);
	      cx++;
	    }

	  if (cx>39)
	    {
	      cx=0;
	      cy++;
	    }
	  
	  if (cy>19)
	    {
	      save=1;
	      editing_done=1;
	    }
	  
	  POKE(764,255);
	  set_cursor();
	}
    }

  if (save==1)
    {
      unsigned char tmp;
      set_cursor_off();
      entry_write(e);
      tmp=num_entries_get();
      if (tmp>=e)
	num_entries_put(++e); // careful increment ordering!
    }

  goto reload;
  
}

/**
 * New entry
 */
void ui_new_entry(void)
{
  unsigned char ne=num_entries_get();
  ui_entry(ne);
}

void ui_read_last(void)
{
  unsigned char ne=num_entries_get();
  if (ne==1)
    ne=1;
  else
    ne--;
  ui_entry(ne);
}

/**
 * Run format UI
 */
void ui_format(void)
{
  print_string(0,8,"Are you sure? \xae");
  POKE(764,255); // REALLY clear the keyboard.
  k=cgetc();

  if (k=='Y')
    {
      SetChar(14,8,57);
      print_string(0,10,"Formatting Disk...");
      format_disk(1);
      bootsect_write(1);
      blank_write(1);
    }
}

/**
 * Run the UI
 */
void ui_run(void)
{
  while (running)
    {
      clear_screen();
      print_string(4,0,"NINA'S DIARY");
      
      print_string(0,2,"Insert \x80\xA4\xA9\xA1\xb2\xb9\x80 Disk.");
      
      print_string(0,4,"Press  \x80\xb3\xb4\xa1\xb2\xb4\x80\x80 to write something new.");
      print_string(7,5,"\x80\xb3\xa5\xac\xa5\xa3\xb4\x80 to read last entry.");
      print_string(7,6,"\x80\xaf\xb0\xb4\xa9\xaf\xae\x80 to format new disk.");
      
      print_string(8,12,"Love you so much. -Mom and Dad");

      // Debounce the console keys.
      while (PEEK(0xD01F)!=0x07) {}     
      while (PEEK(0xD01F)==0x07) {}
      
      switch (PEEK(0xD01F))
	{
	case 6:
	  // Start
	  ui_new_entry();
	  break;
	case 5:
	  // Select
	  ui_read_last();
	  break;	  
	case 3:
	  // Option
	  ui_format();
	  break;
	}
    }
}

