#include <stdio.h>
#include <stdarg.h>
#include "utils.h"

#define BUFFER_SIZE 4096

void mat_log(
  FILE* stream,
  const char* file_name,
  unsigned int line,
  const char* format,
  ...
) {
#if DEBUG_TRUE
  va_list argp;
  va_start(argp, format);
  mat_vlog(stream, file_name, line, format, argp);
  va_end(argp);
#endif
}

void mat_vlog(
  FILE* stream,
  const char *file_name,
  unsigned int line,
  const char *format,
  va_list argp
){
#if DEBUG_TRUE
  char buffer[BUFFER_SIZE];
  char* level;
  int stop;

  if (stderr == stream) {
      level = "ERROR";
  } else if (stdout == stream) {
      level = "INFO";
  }

  // Formating string and
  // Check if the the string has been completly written and
  // no buffer overflow occured
  stop = vsnprintf(buffer, BUFFER_SIZE, format, argp);
  if (stop < BUFFER_SIZE && stop > 0) {
    fprintf(stream, "[%s:%d] [%s] %s\n", file_name, line, level, buffer);
  }
#endif
}

double matrix_rand_interval(double min, double max) {
  double d;
  d = (double) rand() / ((double) RAND_MAX + 1);
  return (min + d * (max - min));
}
