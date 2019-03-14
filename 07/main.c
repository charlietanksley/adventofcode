#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <assert.h>
#include <stdbool.h>

#include "../utils.h"


/* #define FULL_DATA */

#ifdef FULL_DATA
#define INPUT "../input/07-full.txt"
#define NUM_LINES 101
#else
#define INPUT "../input/07-test.txt"
#define NUM_LINES 7
#endif
#define LINE_LENGTH 50

typedef struct {
  char step;
  char dependency;
} Ordering;

void convertLinesToOrderings(char *lines[ ], Ordering *steps[ ], size_t numLines)
{
  int i = 0;
  for ( ; i < (int)numLines; i++) {
    Ordering *ordering = NULL;
    if ((ordering = malloc(sizeof(struct Ordering *))) != NULL) {
      char *line = lines[i];
      sscanf(line, "Step %c must be finished before step %c can begin.", &ordering->dependency, &ordering->step);
      steps[i] = ordering;
    }
  }
}

int main()
{
  int i, j;
  // Read in the file
  char *lines[NUM_LINES];
  size_t linesProcessed = readFile(lines, INPUT, LINE_LENGTH);
  // Sanity check the reading
  /* int i = 0; */
  /* for ( ; i < NUM_LINES; i++) { */
  /*   printf("Line: %s\n", lines[i]); */
  /* } */
  /* printf("num lines %lu\n", linesProcessed); */ 

  // Create an array of depencencies
  Ordering *steps[NUM_LINES];
  convertLinesToOrderings(lines, steps, linesProcessed);
  // Sanity check the dependencies
  for (i = 0; i < NUM_LINES; i++) {
    printf("Step: %c; Dependency: %c\n", steps[i]->step, steps[i]->dependency);
  }

  // I know I want to generate a list of all the steps.
  // Can I put this in a function to get it out of the way?
  char *possibleSteps[26] = {0};
  for (i = 0; i < NUM_LINES; i++) {
    ++possibleSteps[steps[i]->step - 65];
  }
  for (i = 0; i < NUM_LINES; i++) {
    ++possibleSteps[steps[i]->dependency - 65];
  }

  int activeStepCount = 0;
  for (i = 0; i < 26; i++) {
    if (possibleSteps[i] > 0)
      ++activeStepCount;
  }
  int allSteps[activeStepCount];
  int requiredSteps = 0;
  for (i = 0; i < 26; i++) {
    if (possibleSteps[i] > 0) {
      allSteps[requiredSteps] = i + 65;
      ++requiredSteps;
    }
  }

  for (i = 0; i < requiredSteps; i++) {
    printf("Step: %c\n", allSteps[i]);
  }

  int stepOrder[requiredSteps];

  // Some step has to have no prereqs. Do that first.
  for (i = 0; i < requiredSteps; i++) { // Look at each possible step
    _Bool hasDependency = false;
    for (j = 0; j < (int)linesProcessed; j++) { // Look at each known dependency
      if (allSteps[i] == steps[j]->step) { // If the current possible step matches one with a dependency
        hasDependency = true;
        break;
      }
    }
    if (hasDependency == false) {
      stepOrder[0] = allSteps[i];
    }
  }

  // Now let's walk through the other steps and add in ones we can
  for (i = 1; i < requiredSteps; i++) {
    stepOrder[i] = getNextStep(allSteps, stepOrder, steps);
    printf("%c", allSteps[i]);
  }
  printf("\n");

  printf("The first step: %c\n", stepOrder[0]);
  return 0;
}
