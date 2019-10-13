/**
 * Nina's Diary
 *
 * Author: Thomas Cherryhomes
 *  <thom.cherryhomes@gmail.com>
 *
 * Configuration constants
 */

/**
 * Define information:
 * -------------------
 *
 * SINGLE_DENSITY use 128 byte sectors
 * DOUBLE_DENSITY use 256 byte sectors
 *
 * SSSD - Single Sided / Single Density / 720 sectors, 128 bytes/sec, 18 sec/trk, giving 90 total pages. (Atari 810 and compatible drives)
 * SSED - Single Sided / Medium Density / 1040 sectors, 128 bytes/sec, 26 sec/trk,  giving 130 total pages. (Atari 1050 and compatible drives)
 * SSDD - Single Sided / Double Density / 720 sectors, 256 bytes/sec, 18 sec/trk, giving 180 total pages. 
 * DSDD - Double Sided / Double Density / 1440 sectors, 256 bytes/sec, 18 sec/trk, giving 360 total pages.
 * DSQD - Double Sided / Quad   Density / 2880 sectors, 256 bytes/sec, 18 sec/trk, giving 720 total pages.
 *
 * TOTAL_SECTORS  - Total # of sectors on disk
 * FORMAT_COMMAND - The format command to use 
 * TOTAL_PAGES    - Total # of pages on disk
 * PERCOM_CONFIG  - Whether to send a write PERCOM block before formatting to configure drive.
 * PERCOM_TRACKS  - # of tracks on disk
 * PERCOM_SPT     - Specify # of sectors per track (typically 18 or 26)
 * PERCOM_SIDES   - Specify # of sides on disk (0 or 1)
 * PERCOM_DENSITY - 0 for FM, 4 for MFM
 * PERCOM_SECTORH - hi-byte for sector size
 * PERCOM_SECTORL - lo-byte for sector size
 *
 * SECTOR_SIZE    - size of sector in bytes
 * NUM_SECTORS    - # of sectors in an entry
 * ENTRY_SHIFT    - amount to shift to convert entry # to sector #
 * VIDEO_SHIFT    - amount to shift to convert sector offset to video ram offset
 */

#ifndef CONFIG_H
#define CONFIG_H

/* Set the desired drive config here */
#define DSQD 1

#ifdef SSSD
#define SINGLE_DENSITY 1
#define TOTAL_SECTORS 720
#define FORMAT_COMMAND 0x21
#define TOTAL_PAGES 90
#endif /* SSSD */

#ifdef SSED
#define SINGLE_DENSITY 1
#define TOTAL_SECTORS 1040
#define FORMAT_COMMAND 0x22
#define TOTAL_PAGES 130
#endif /* SSSD */

#ifdef SSDD
#define DOUBLE_DENSITY 1
#define TOTAL_SECTORS 720
#define FORMAT_COMMAND 0x21
#define TOTAL_PAGES 180
#define PERCOM_CONFIG 1
#define PERCOM_TRACKS 40
#define PERCOM_SPT 18
#define PERCOM_SIDES 0
#define PERCOM_DENSITY 4 // (MFM)
#define PERCOM_SECTORH 1 // 256
#define PERCOM_SECTORL 0 // 256
#endif

#ifdef DSDD
#define DOUBLE_DENSITY 1
#define TOTAL_SECTORS 1440
#define TOTAL_PAGES 360
#define FORMAT_COMMAND 0x21
#define PERCOM_CONFIG 1
#define PERCOM_TRACKS 40
#define PERCOM_SPT 18
#define PERCOM_SIDES 1
#define PERCOM_DENSITY 4 // (MFM)
#define PERCOM_SECTORH 1 // 256
#define PERCOM_SECTORL 0 // 256
#endif

#ifdef DSQD
#define DOUBLE_DENSITY 1
#define TOTAL_SECTORS 2880
#define TOTAL_PAGES 720
#define FORMAT_COMMAND 0x21
#define PERCOM_CONFIG 1
#define PERCOM_TRACKS 80
#define PERCOM_SPT 18
#define PERCOM_SIDES 1
#define PERCOM_DENSITY 4 // (MFM)
#define PERCOM_SECTORH 1 // 256
#define PERCOM_SECTORL 0 // 256
#endif

#ifdef SINGLE_DENSITY
#define ENTRY_START_SECTOR 8
#define SECTOR_SIZE 128
#define NUM_SECTORS 8
#define ENTRY_SHIFT 3
#define VIDEO_SHIFT 7
#endif /* SINGLE_DENSITY */

#ifdef DOUBLE_DENSITY
#define ENTRY_START_SECTOR 4
#define SECTOR_SIZE 256
#define NUM_SECTORS 4
#define ENTRY_SHIFT 2
#define VIDEO_SHIFT 8
#endif /* DOUBLE_DENSITY */

#endif /* CONFIG_H */
