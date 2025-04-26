#include "level.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int **load_csv(const char *filename, int *rows, int *cols) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("Could not open file");
    return NULL;
  }

  char line[1024];
  int **map = NULL;
  int row_count = 0;
  int column_count = 0;

  while (fgets(line, sizeof(line), file)) {
    // Trim newline
    line[strcspn(line, "\r\n")] = 0;

    // Count columns on first row
    if (row_count == 0) {
      char *tmp = strdup(line);
      char *token = strtok(tmp, ",");
      while (token) {
        column_count++;
        token = strtok(NULL, ",");
      }
      free(tmp);
    }

    // Allocate row
    int **new_map = realloc(map, sizeof(int *) * (row_count + 1));
    if (!new_map) {
      perror("Memory allocation failed");
      fclose(file);
      return NULL;
    }
    map = new_map;
    map[row_count] = malloc(sizeof(int) * column_count);

    // Parse row
    char *token = strtok(line, ",");
    int col = 0;
    while (token && col < column_count) {
      map[row_count][col++] = atoi(token);
      token = strtok(NULL, ",");
    }

    // If not enough columns, fill remaining with 0s
    while (col < column_count) {
      map[row_count][col++] = 0;
    }

    row_count++;
  }

  fclose(file);
  *rows = row_count;
  *cols = column_count;
  return map;
}
