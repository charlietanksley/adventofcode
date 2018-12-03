#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINE_LENGTH 500
#define INPUT_FULL "../input/03-full.txt"
#define INPUT_TEST "../input/03-test-one.txt"
#define INPUT INPUT_FULL

#define SIDE_LENGTH_FULL 1000
#define SIDE_LENGTH_TEST 8
#define SIDE_LENGTH SIDE_LENGTH_FULL

int numberIn(int num, int lst[], int lstSize)
{
  int i;
  for (i = 0; i < lstSize; i++) {
    if (num == lst[i]) {
      return 1;
    }
  }

  return 0;
}

int isCleanSquare(int lst[], int lstSize)
{
  int i;
  for (i = 0; i < lstSize; i++) {
    if (lst[i] == 0) {
      return 0;
    }
  }

  return 1;
}

int main()
{
  FILE *fp;
  fp = fopen(INPUT, "r");
  if (fp == NULL) {
    perror(INPUT);
    exit(EXIT_FAILURE);
  }

  char *claims[2000];
  char line[LINE_LENGTH];

  int numClaims = 0, i = 0;
  size_t lineLength = 0;

  while (fgets(line, LINE_LENGTH * sizeof(char), fp) != NULL) {
    char *linePtr = NULL;

    line[strcspn(line, "\r\n")] = 0;
    ++numClaims;

    if (lineLength == 0)
      lineLength = strlen(line);

    if ((linePtr = malloc(lineLength)) != NULL) {
      strcpy(linePtr, line);
    }

    claims[i] = linePtr;
    ++i;
  }

  printf("We ran and slurped %d lines!\n", numClaims);

  // Part 1 - 115242

  int squareInches[SIDE_LENGTH * SIDE_LENGTH];
  int claimsProcessed = 0;

  for ( ; claimsProcessed < numClaims; claimsProcessed++) {
    char *claimPtr = claims[claimsProcessed];
    int elfId, left, top, width, height;
    sscanf(claimPtr, "#%d @ %d,%d: %dx%d", &elfId, &left, &top, &width, &height);

    int startingSquare = (SIDE_LENGTH * top) + left;

    int j;
    // Across

    // This is off in some very strange way.
    for (i = 0; i < width; i++) {
      int id = startingSquare + i;
      ++squareInches[id];

      for (j = 1; j < height; j++) {
        ++squareInches[id + (j * SIDE_LENGTH)];
      }
    }
  }

  int overlaps = 0;
  for (i = 0; i < SIDE_LENGTH * SIDE_LENGTH; i++) {
    if (squareInches[i] > 1) {
      ++overlaps;
    }
  }
  printf("There were %d overlaps\n", overlaps);

  // Part 2 - 1046
  // Get all the squares that are only used once.
  int cleanSquareCounter = 0;
  int cleanSquares[(SIDE_LENGTH * SIDE_LENGTH) - overlaps];

  for (i = 0; i < SIDE_LENGTH * SIDE_LENGTH; i++) {
    if (squareInches[i] == 1) {
      cleanSquares[cleanSquareCounter] = i;
      ++cleanSquareCounter;
    }
  }

  // Walk through the claims again and bail when I find a clean one.
  int cleanElfId = 0;

  for (claimsProcessed = 0 ; claimsProcessed < numClaims; claimsProcessed++) {
    char *claimPtr = claims[claimsProcessed];
    int elfId, left, top, width, height;
    sscanf(claimPtr, "#%d @ %d,%d: %dx%d", &elfId, &left, &top, &width, &height);

    int startingSquare = (SIDE_LENGTH * top) + left;
    int squaresUsed[SIDE_LENGTH];
    int squaresUsedCounter = 0;
    int j;

    // Reuses the logic from part 1 to build a list of used squares
    // for this claim
    for (i = 0; i < width; i++) {
      int id = startingSquare + i;
      squaresUsed[squaresUsedCounter] = id;
      ++squaresUsedCounter;

      for (j = 1; j < height; j++) {
        int id2 = id + (j * SIDE_LENGTH);
        squaresUsed[squaresUsedCounter] = id2;
        ++squaresUsedCounter;
      }
    }

    int usedSquareTracker[squaresUsedCounter];
    for (i = 0; i < squaresUsedCounter; i++) {
      usedSquareTracker[i] = numberIn(squaresUsed[i], cleanSquares, cleanSquareCounter);
    }

    printf("Looking at elfId: %d\n", elfId);
    if (isCleanSquare(usedSquareTracker, squaresUsedCounter) == 1) {
      cleanElfId = elfId;
      break;
    }
  }

  printf("The elf with a clean square: %d\n", cleanElfId);

  return 0;
}
