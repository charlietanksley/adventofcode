#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INPUT "../input/01-01.txt"

int main()
{
  FILE *fp;
  fp = fopen(INPUT, "r");
  if (fp == NULL) {
    perror(INPUT);
    exit(EXIT_FAILURE);
  }

  struct ChangeDirection {
    int size;
    char direction;
  };

  char line[1000];
  struct ChangeDirection changes[10000];

  int changeCount = 0;
  while (fgets(line, 1000 * sizeof(char), fp) != NULL) {
    struct ChangeDirection c;
    c.direction = line[0];
    c.size = atoi(&line[1]);
    changes[changeCount] = c;
    changeCount = changeCount + 1;
  }

  fclose(fp);

  int j, k, frequency = 0, step = 1;
  int frequencies[1000000];
  int x = 1;
  frequencies[0] = 0;

  // change this to x < 2 if you want to only run through once.
  int cond = x > 0;

  while(cond) {
    x = x + 1;
    for (j = 0; j < changeCount; j++) {
      if (('+' == changes[j].direction) == 1) {
        frequency = frequency + changes[j].size;
      } else {
        frequency = frequency - changes[j].size;
      }
      for (k = 0; k < step; k++) {
        if (frequencies[k] == frequency) {
          printf("Repeated Frequency: %d\n", frequency);
          return 0;
        }
      }
      frequencies[step] = frequency;
      step = step + 1;
    }
  }

  printf("Frequency: %d\n", frequency);
  return 0;
}
