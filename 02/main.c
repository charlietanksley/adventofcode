#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INPUT_FULL "../input/02-full.txt"
#define INPUT_TEST_ONE "../input/02-test.txt"
#define INPUT_TEST_TWO "../input/02-test-two.txt"
#define INPUT INPUT_FULL


// Stolen from C in a nutshell)
int str_compare(const void *p1, const void *p2)
{
  return strcmp(*(char **)p1, *(char **)p2);
}

int main()
{

  FILE *fp;
  fp = fopen(INPUT, "r");
  if (fp == NULL) {
    perror(INPUT);
    exit(EXIT_FAILURE);
  }

  char line[1000];
  int twos = 0, threes = 0, i = 0, numLines = 0;

  char *ids[1000];

  while (fgets(line, 1000 * sizeof(char), fp) != NULL) {
    char *linePtr = NULL;

    line[strcspn(line, "\r\n")] = 0;
    numLines = numLines + 1;

    size_t len = strlen(line);
    if ( (linePtr = malloc(len)) != NULL ) {
      strcpy(linePtr, line);
    }
    ids[i] = linePtr;
    i = i + 1;
  }

  fclose(fp);

  // Part 1
  int j = 0;
  for ( ; j < numLines; j++) {
    char *linePtr = ids[j];

    int lineLength = strlen(linePtr);
    int characters[26] = {0};

    for (i = 0; i < lineLength; i++) {
      int index = linePtr[i] - 'a';
      characters[index] = characters[index] + 1;
    }

    // Look for 2s first
    for (i = 0; i < 26; i++) {
      if (characters[i] == 2) {
        twos = twos + 1;
        break;
      }
    }

    // Look for 3s
    for (i = 0; i < 26; i++) {
      if (characters[i] == 3) {
        threes = threes + 1;
        break;
      }
    }
  }

  printf("Twos: %d, Threes: %d\n", twos, threes);

  printf("Checksum: %d\n", twos * threes);

  // Part 2
  qsort(ids, numLines, sizeof(char*), str_compare); // sorted. Woah.

  int lineLength = strlen(ids[0]);

  for (i = 0; i < numLines - 1; i++) {
    char *currentLinePtr = ids[i];
    char *nextLinePtr = ids[i+1];

    int missed = 0, matches = 0;
    char match[lineLength];
    strcpy(match, "");

    for (j = 0; j < lineLength; j++) {
      if (currentLinePtr[j] == nextLinePtr[j]) {
        match[matches] = currentLinePtr[j];
        matches++;
      } else {
        missed++;
      }
    }

    if (missed == 1) {
      match[lineLength - 1] = '\0';
      printf("ID: %s\n", match);
      break;
    }
  }

  return 0;
}


