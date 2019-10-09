/**
 * Nina's Diary
 *
 * Author: Thomas Cherryhomes
 *  <thom.cherryhomes@gmail.com>
 *
 * Main routines
 */

#include "ui.h"

void main(void)
{
  ui_setup();
  
  for (;;)
    ui_run();
}
