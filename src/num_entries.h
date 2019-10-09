/**
 * Nina's Diary
 *
 * Author: Thomas Cherryhomes
 *  <thom.cherryhomes@gmail.com>
 *
 * Get/Put # of entries.
 */

#ifndef NUM_ENTRIES_H
#define NUM_ENTRIES_H

/**
 * Get number of entries available on disk
 */
unsigned char num_entries_get(void);

/**
 * Put entries back onto disk (use num_entries_get_first!) 
 */
void num_entries_put(unsigned char num_entries);

#endif /* NUM_ENTRIES_H */
