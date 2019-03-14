#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printCharArray(char arr[ ], int len)
{
  int i = 0;
  for ( ; i < len; i++) {
    printf("%c, ", arr[i]);
  }
  printf("\n");
}

void printIntArray(int arr[ ], int len)
{
  int i = 0;
  for ( ; i < len; i++) {
    printf("%d, ", arr[i]);
  }
  printf("\n");
}

size_t readFile(char *lines[ ], char *filename, int lineLength)
{
  // Read the file
  FILE *fp;
  fp = fopen(filename, "r");
  if (fp == NULL) {
    perror(filename);
    exit(EXIT_FAILURE);
  }

  // Put the lines in an array of pointers
  char line[lineLength + 1];
  size_t linesProcessed = 0;

  while (fgets(line, lineLength * sizeof(char), fp) != NULL) {
    char *linePtr = NULL;
    line[strcspn(line, "\r\n")] = 0;

    if ((linePtr = malloc(strlen(line) + 1)) != NULL) {
      strcpy(linePtr, line);
    }
    lines[linesProcessed] = linePtr;
    ++linesProcessed;
  }

  // We can close the file now
  fclose(fp);

  return linesProcessed;
}
