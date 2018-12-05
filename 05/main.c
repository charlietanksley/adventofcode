#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FULL_DATA true

#ifdef FULL_DATA
#define INPUT "../input/05-full.txt"
#define LOG_LENGTH 50001
#else
#define INPUT "../input/05-test.txt"
#define LOG_LENGTH 17
#endif

int isLower(char c)
{
  return c > 96;
}

char downcase(char c)
{
  if (isLower(c) == 1) {
    return c;
  } else {
    return c + 32;
  }
}

int removeChar (char **str, char character)
{
  int lenBefore = strlen(*str);
  char *outStr = NULL;
  outStr = malloc((lenBefore + 1) * sizeof(char));
  char *ms = NULL;
  ms = malloc((lenBefore + 1) * sizeof(char));
  strcpy(ms, *str);

  int copied = 0, i;
  for (i = 0; i < lenBefore; i++) {
    if (downcase(ms[i]) != character) {
      outStr[copied] = ms[i];
      ++copied;
    }
  }

  outStr[copied] = '\0';
  strcpy(*str, outStr);

  int lenAfter = strlen(outStr);
  return lenAfter;
}

int stripMatches(char **str)
{
  int lenBefore = strlen(*str);
  char *matchedStr = NULL;
  matchedStr = malloc((lenBefore + 1) * sizeof(char));
  char *ms = NULL;
  if ((ms = malloc((lenBefore + 1) * sizeof(char))) != NULL) {
    strcpy(ms, *str);
  } else {
    exit(EXIT_FAILURE);
  }

  int i, copied = 0;

  for (i = 0; i < lenBefore; i++) {
    char this = ms[i], that = ms[i + 1];

    /* printf("Char: %c, Is lower: %d, downcased: %c\n", this, isLower(this), downcase(this)); */
    if (isLower(this) == isLower(that)) { // if they are the same case, move on
      matchedStr[copied] = ms[i];
      ++copied;
    } else {
      if ((downcase(this) == downcase(that)) == 1) { // if they are the different case of the same letter
        ++i;
      } else {
        matchedStr[copied] = ms[i];
        ++copied;
      }
    }
  }

  matchedStr[copied + 1] = '\0';
  *str = matchedStr;

  return strlen(*str);
}

int main()
{
  FILE *fp;
  fp = fopen(INPUT, "r");
  if (fp == NULL) {
    perror(INPUT);
    exit(EXIT_FAILURE);
  }

  char line[LOG_LENGTH];
  /* while (fgets(line, LOG_LENGTH * sizeof(char), fp) != NULL) { */
  fgets(line, LOG_LENGTH * sizeof(char), fp);

  line[strcspn(line, "\n\r")] = 0;

  /* Part 1 */
  char *pt1Str = NULL;
  if ((pt1Str = malloc(strlen(line) + 1)) != NULL) {
    strcpy(pt1Str, line);
  } else {
    exit(EXIT_FAILURE);
  }

  int str1LenAfter = 0, str1LenBefore;
  str1LenBefore = strlen(pt1Str);
  while (1) {
    str1LenBefore = strlen(pt1Str);
    str1LenAfter = stripMatches(&pt1Str);
    /* printf("beflre: %d, after: %d\n", str1LenBefore, str1LenAfter); */
    if (str1LenAfter == str1LenBefore) {
      break;
    }
  }


  printf("The length: %d\n", str1LenAfter);

  // Part 2
  int shortest = LOG_LENGTH;
  char a;
  for (a = 'a'; a < 'z'; a++) {
    char *strPtr = NULL;
    if ((strPtr = malloc(strlen(line) + 1)) != NULL) {
      strcpy(strPtr, line);
    } else {
      exit(EXIT_FAILURE);
    }

    removeChar(&strPtr, a);

    int str2LenAfter = 0, str2LenBefore;
    str2LenBefore = strlen(strPtr);
    while (1) {
      str2LenBefore = strlen(strPtr);
      str2LenAfter = stripMatches(&strPtr);
      if (str2LenAfter == str2LenBefore) {
        break;
      }
    }

    /* printf("Removed %c and left %d characters: %s\n", a, str2LenAfter, strPtr); */
    if (str2LenAfter < shortest) {
      shortest = str2LenAfter;
    }
  }
  printf("Shortest possible: %d\n", shortest);


  return 0;
}
