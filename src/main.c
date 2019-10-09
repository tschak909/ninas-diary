/**
 * Nina's Diary
 *
 * Author: Thomas Cherryhomes
 *  <thom.cherryhomes@gmail.com>
 *
 * Main routines
 */

#include "ui.h"

unsigned char running=1;
unsigned char buf[128];

void main(void)
{
  ui_setup();

  __asm__("jsr $E450");
  
  while (running)
    ui_run();

  __asm__("jsr $e477");

}
