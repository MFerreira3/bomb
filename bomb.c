#include <stdio.h>
#include <string.h>

int main(int argc, char*argv[]) {
  FILE *fp;
  char instruction;

  if (argc != 2) {
    printf("One argument expected.\n");
    return -1;
  }

  fp = fopen(argv[1], "r");
  instruction = fgetc(fp);

  while (instruction != EOF) {
    printf("%c", instruction);
    instruction = fgetc(fp);
  }

  
  printf("\n");
  return fclose(fp);
}
