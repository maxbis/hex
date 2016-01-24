/* Small prgramm to list a file (txt or bin) in hex format */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    char ch;
    FILE *fp;

    if ( argc == 1 ) {
        fp = stdin;
    } 

    if ( argc == 2 ) {
        if ((fp = fopen( argv[1], "rb")) == NULL ) {
            perror("Error opening file");
            return EXIT_FAILURE;
        }
    } 

   int i=0;
   char line[17];
   
   line[16]='\0';

   printf("%09d: ",i);
   while( ( ch = fgetc(fp) ) != EOF ) {
          printf("%02X ",(unsigned char)ch);
          if ( ch>=32 && ch<=126 ) {
             line[i%16] = ch;
          } else {
             line[i%16] = '.';
          }
          if( !(++i % 16) ) {
              printf("  %s\n%09d: ",line, i);
          } else {	
              if ( !(i%8) ) printf(" ");
          }
   }
   line[i%16] = '\0';

   while ( i%16 ) {     
       if ( !(i%8) ) printf(" ");
       printf("   ");
       i++;
   }
   printf("  %s\n",line);
   fclose(fp);
   putc('\n', stdout);

   return 0;
}
