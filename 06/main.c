#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <assert.h>
#include <stdbool.h>

#define FULL_DATA

#ifdef FULL_DATA
#define INPUT "../input/06-full.txt"
#define NUM_LINES 50
#else
#define INPUT "../input/06-test.txt"
#define NUM_LINES 6
#endif
#define LINE_LENGTH 10

struct Point {
  int x;
  int y;
  int pointsInArea;
};

// I could make these faster by using qsort and just getting the X and
// Y coordinates once.
int top(struct Point points[], int numPoints)
{
  int i, top;
  for (i = 0; i < numPoints; i++) {
    int y = points[i].y;
    if (i == 0) {
      top = y;
    } else if (y < top) {
      top = y;
    }
  }

  return top;
}

int bottom(struct Point points[], int numPoints)
{
  int i, bottom;
  for (i = 0; i < numPoints; i++) {
    int y = points[i].y;
    if (i == 0) {
      bottom = y;
    } else if (y > bottom) {
      bottom = y;
    }
  }

  return bottom;
}

int left(struct Point points[], int numPoints)
{
  int i, left;
  for (i = 0; i < numPoints; i++) {
    int x = points[i].x;
    if (i == 0) {
      left = x;
    } else if (x < left) {
      left = x;
    }
  }

  return left;
}

int right(struct Point points[], int numPoints)
{
  int i, right;
  for (i = 0; i < numPoints; i++) {
    int x = points[i].x;
    if (i == 0) {
      right = x;
    } else if (x > right) {
      right = x;
    }
  }

  return right;
}

int manhattanDistance(struct Point p1, struct Point p2)
{
  return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

int main()
{
  int i, j;

  // Read the file
  FILE *fp;
  fp = fopen(INPUT, "r");
  if (fp == NULL) {
    perror(INPUT);
    exit(EXIT_FAILURE);
  }

  // Put the lines in an array of pointers
  char line[LINE_LENGTH];
  char *lines[NUM_LINES];
  int linesProcessed = 0;

  while (fgets(line, LINE_LENGTH * sizeof(char), fp) != NULL) {
    char *linePtr = NULL;
    line[strcspn(line, "\r\n")] = 0;

    if ((linePtr = malloc(strlen(line))) != NULL) {
      strcpy(linePtr, line);
    }
    lines[linesProcessed] = linePtr;
    ++linesProcessed;
  }

  // We can close the file now
  fclose(fp);

  // Create the grid
  struct Point points[linesProcessed];

  for (i = 0; i < linesProcessed; i++) {
    struct Point point;
    char *line = lines[i];
    sscanf(line, "%d, %d", &point.x, &point.y);
    point.pointsInArea = 0;
    points[i] = point;
  }

  for (i = 0; i < linesProcessed; i++) {
    struct Point point = points[i];
    printf("X: %d, Y: %d\n", point.x, point.y);
  }

  int minY = top(points, linesProcessed);
  int maxY = bottom(points, linesProcessed);
  int minX = left(points, linesProcessed);
  int maxX = right(points, linesProcessed);
  printf("Top: %d\n", minY);
  printf("Bottom: %d\n", maxY);
  printf("Left: %d\n", minX);
  printf("Right: %d\n", maxX);

  int gridWidth = maxX - minX + 1;
  int gridHeight = maxY - minY + 1;
  int numElements = gridWidth * gridHeight;
  printf("Size: %dx%d\n", gridWidth, gridHeight);


  // Okay, so this isn't working. Most likely because I need to be
  // mallocing these structs and passing around pointers. I can either:
  //
  // 1. Figure that out.
  //
  // 2. Just do the whole 'calculation' here (instead of storing the
  // points off) and just tally the counter for my winning point.
  int elementCount = 0;
  struct Point grid[numElements];
  int sizeOfSafeRegion = 0;
  for (i = minY; i <= maxY; i++) {
    for (j = minX; j <= maxX; j++) {
      struct Point point;
      point.x = j;
      point.y = i;
      grid[elementCount] = point;
      ++elementCount;

      int distances[linesProcessed];
      int k;
      for (k = 0; k < linesProcessed; k++) {
        distances[k] = manhattanDistance(points[k], point);
      }

      int minDistance = 1000; // Ideally this would be the biggest number
      int minId = 1000; // Same
      for (k = 0; k < linesProcessed; k++) {
        if (distances[k] == minDistance) {
          minId = 1000;
        } else if (distances[k] < minDistance) {
          minDistance = distances[k];
          minId = k;
        }
      }

      if (minId < 1000) {
        ++points[minId].pointsInArea;
      }

      int distanceSum = 0;
      for (k = 0; k < linesProcessed; k++) {
        distanceSum = distanceSum + distances[k];
      }

      // 38670 for Part 2
      if (distanceSum < 10000) {
        ++sizeOfSafeRegion;
      }
    }
  }

  printf("Processed %d elements\n", elementCount);

  // I should really sort this list :/
  for (i = 0; i < linesProcessed; i++) {
    printf("X: %d, Y: %d, Area: %d\n", points[i].x, points[i].y, points[i].pointsInArea);
  }

  printf("Size of safe region: %d\n", sizeOfSafeRegion);

  return 0;
}
