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
#include "ui.h"
#include "charset.h"

static unsigned char* dlist_ptr;
static unsigned char* video_ptr;
static unsigned short screen_memory;
static unsigned char cx,cy,ox,oy;

#define SetChar(x,y,a) video_ptr[(x)+(y)*40]=(a);
#define GetChar(x,y) video_ptr[(x)+(y)*40]
#define GRAPHICS_0_SCREEN_SIZE (40*25)

void clear_screen()
{
  memset(video_ptr,0,GRAPHICS_0_SCREEN_SIZE);
}

void cursor(unsigned char x, unsigned char y)
{
  SetChar(x,y,GetChar(x,y)|0x80);

  if (ox==0xff)
    return;

  SetChar(x,y,GetChar(x,y)&0x7F);
}

void print_string(unsigned char x,unsigned char y,char *s)
{
  do
    {
      if (*s < 32)
	{
	  SetChar(x++,y,*s+64);
	}
      else if (*s<96)
	{
	  SetChar(x++,y,*s-32);
	}
      else
	{
	  SetChar(x++,y,*s);
	}
      ++s;
    } while(*s!=0);
}

/**
 * Set up the display
 */
void ui_setup(void)
{
  POKE(708,154);
  POKE(709,15);
  POKE(710,69);
  POKE(712,69);
  dlist_ptr=(unsigned char *)(PEEKW(560));
  dlist_ptr[3]=0x46;
  dlist_ptr[6]=0x06;
  screen_memory=PEEKW(560)+4;
  video_ptr=(unsigned char*)(PEEKW(screen_memory));
  charset_use();
}

/**
 * Run the UI
 */
void ui_run(void)
{
  clear_screen();
  print_string(0,0,"    NINA'S DIARY");

  print_string(0,2,"Insert \x80\xA4\xA9\xA1\xb2\xb9\x80 Disk.");

  print_string(0,4,"Press  \x80\xb3\xb4\xa1\xb2\xb4\x80\x80 to write something new.");
  print_string(7,5,"\x80\xb3\xa5\xac\xa5\xa3\xb4\x80 to format new disk.");
  print_string(7,6,"\x80\xaf\xb0\xb4\xa9\xaf\xae\x80 to read.");

  print_string(8,20,"Love you so much. -Mom and Dad");
  
  for (;;) {}
}

