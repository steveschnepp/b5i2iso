#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 *  $Id: b5i2iso.c, 01/09/04 07.18
 *
 *
 *  Licensed under the terms of the GNU GPL License version 2.
 *
 *  First version  Salvatore Santagati salsan1982@users.sourceforge.net
 *
 *  This is a very simple utility to convert a BlindWrite BIN image to standard ISO format
 *  This programm is based from bin2iso by DeXT
 *
 *
 *
 */

int main( int argc, char **argv )
{
	int   seek_ecc, sector_size,bw=1;
	long  i, source_length;
	char  buf[2448], destfilename[2354];
	FILE  *fdest, *fsource;
	const char SYNC_HEADER[12] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

if (argc < 2)
   {
	printf("Error: bad syntax\n\nUsage is: b5i2iso image.b5i [image.iso]\n");
	exit(EXIT_FAILURE);
   }

if (argc >= 3)
   {
	strcpy(destfilename, argv[2]);
   }
else
   {
	strcpy(destfilename, argv[1]);
	if (strlen(argv[1]) < 5 || strcmp(destfilename+strlen(argv[1])-4, ".b5i"))
		strcpy(destfilename+strlen(argv[1]), ".iso");
	else
		strcpy(destfilename+strlen(argv[1])-4, ".iso");
   }

fsource = fopen(argv[1],"rb");
fdest = fopen(destfilename,"wb");

fseek(fsource, 2352, SEEK_CUR);

fread(buf, sizeof(char), 16, fsource);



if (!memcmp(SYNC_HEADER, buf, 12))

  {
		/* BAD IMAGE BLINDWRITE */
		seek_ecc = 384;
		sector_size = 2448;

		}

   else
      {
		/* NORMAL IMAGE BLINDWRITE */
	seek_ecc = 288;
	sector_size = 2352;
	  }


fseek(fsource, 0L, SEEK_END);
source_length = ftell(fsource)/sector_size;
fseek(fsource, 0L, SEEK_SET);

for(i = 0; i < source_length; i++)
   {
	fseek(fsource, 16, SEEK_CUR); /* seek_header = 16 */
    fread(buf, sizeof(char), 2048, fsource);
	if (bw >150) fwrite(buf, sizeof(char), 2048, fdest);
    fseek(fsource, seek_ecc, SEEK_CUR);
    bw++;
   }

fclose(fdest);
fclose(fsource);

exit(EXIT_SUCCESS);
}
