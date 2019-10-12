/**
 * Nina's Diary
 *
 * Author: Thomas Cherryhomes
 *  <thom.cherryhomes@gmail.com>
 *
 * Main routines
 */

#include <atari.h>
#include "ui.h"

unsigned char running=1;
unsigned char buf[256];

void main(void)
{
  ui_setup();

  OS.bootq=1;
  OS.coldst=255;
  
  __asm__("jsr $E450");
  
  while (running)
    ui_run();

  __asm__("jsr $e477");

}
