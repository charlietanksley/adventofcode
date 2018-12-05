#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* #define FULL_DATA false */

#ifdef FULL_DATA
#define INPUT "../input/04-full.txt"
#define LOG_LENGTH 1500
#else
#define INPUT "../input/04-test.txt"
#define LOG_LENGTH 20
#endif

struct Guard {
  int id;
  struct tm shifts[1000];
  struct tm naps[1000];
};

int main()
{

  // I always need counters
  int i, j;

  /*****************************************************************************/
  /********************** Read in the file *************************************/
  /*****************************************************************************/
  FILE *fp;
  fp = fopen(INPUT, "r");
  if (fp == NULL) {
    perror(INPUT);
    exit(EXIT_FAILURE);
  }

  char *logLines[LOG_LENGTH];
  int logLineCount = 0;
  size_t logLineLength = 0;
  char line[1000];

  while (fgets(line, 1000 * sizeof(char), fp) != NULL) {
    char *linePtr = NULL;
    line[strcspn(line, "\n\r")] = 0;

    if (logLineLength == 0)
      logLineLength = strlen(line);

    if ((linePtr = malloc(logLineLength)) != NULL) {
      strcpy(linePtr, line);
    }

    logLines[logLineCount] = linePtr;
    ++logLineCount;
  }

  fclose(fp);

  // Sanity checking our file reading
  int processed = 0;
  for (i = 0; i < logLineCount; i++) {
    if (logLines[i][0] == '[') {
      ++processed;
    }
  }
  printf("We processed %d lines\n", processed);

  /*****************************************************************************/
  /********************** Process lines ****************************************/
  /*****************************************************************************/

  printf("valgrind\n");
  for (i = 0; i < logLineCount; i++) {
    int year, month, day, hour, minute;
    char *body = NULL;
    char *logPtr = logLines[i];

    sscanf(logPtr, "[%d-%d-%d %d:%d] %s", &year, &month, &day, &hour, &minute, body);
    if (body[0] == 'G') {
      printf("Guard\n");
    }
    /* else if (*body == 'w') { */
    /*   printf("wakes\n"); */
    /* } else if (*body == 'f') { */
    /*   printf("falls\n"); */
    /* } else { */
    /*   printf("not expected me\n"); */
    /* } */
  /* Guard #%d begins shift */
  }

  /* sscanf(logLines[0], "[%d-%d-%d %d:%d] Guard #%d begins shift", &year, &month, &day, &hour, &minute, &elfId); */

  /* printf("Hour: %d, elf: %d\n", hour, elfId); */

  /* struct tm first; */
  /* first.tm_year = year; */
  /* first.tm_mon = month; */
  /* first.tm_mday = day; */
  /* first.tm_hour = hour; */
  /* first.tm_min = minute; */
  /* first.tm_isdst = 0; */
  /* printf("Hour: %d, elf: %d\n", first.tm_hour, elfId); */


  /* struct tm second; */
  /* second.tm_year = year; */
  /* second.tm_mon = month; */
  /* second.tm_mday = day; */
  /* second.tm_hour = 01; */
  /* second.tm_min = minute; */

  /* printf("Hour: %d, elf: %d\n", first.tm_hour, elfId); */
  /* printf("Hour 2: %d, elf: %d\n", second.tm_hour, elfId); */
  /* printf("An hour passed: %d\n", (int)difftime(mktime(&first), mktime(&second)) / 60 / 60); */
  return 0;
}
