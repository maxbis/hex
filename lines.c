#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

static void print_lines(FILE* fp, int reqLine) {
  static size_t linum;
  char ch;
  bool newline = true;

  while(EOF != (ch = fgetc(fp))) {
    if(newline) {
      linum++;
      newline = false;
      if ( reqLine == 0 ) {
        printf("%6zu  ", linum);
      }
    }
    if('\n' == ch) {
      newline = true;
    }
    if ( linum == reqLine || reqLine == 0 ) {
      fputc(ch, stdout);
    }
  }
}

static void help(char *thisProgram) {
  printf("Usage: %s [number] [file]\n", thisProgram);
  printf("  number is line number to be printed\n");
  printf("  file file to be read if omiited stdin is used\n");
  exit(0);
}

int main(int argc, char* argv[]) {
  if(argc == 2) {
    FILE *fp = fopen(argv[1], "r");
    if(fp) {
      print_lines(fp, 0);
    } else {
      help(argv[0]);
    }
  } else if (argc == 3) {
    FILE *fp = fopen(argv[2], "r");
    if(!fp) {
        fprintf(stderr, "%s\n", "ERROR: file not found!");
        exit(-1);
      } else {
        print_lines(fp, atoi(argv[1]));
      }
  } else {
    help(argv[0]);
  }
}
