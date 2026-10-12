/*Lab 5, Task 1
  Name: <Murshid Gasimov>
  Student ID: <251ADB074>*/

#include <stdio.h>

int main(void) {
  const char* filename = "data.txt";
  FILE* fp;
  char line[100];
  int lines_read = 0;

  printf("Writing lines to %s...\n", filename);

  fp = fopen(filename, "w");
  if (fp == NULL) {
    perror("Error opening file for writing");
    return 1;
  }

  fprintf(fp, "Hello, file I/O in C!\n");
  fprintf(fp, "This is another line.\n");

  if (fclose(fp) != 0) {
    perror("Error closing file");
    return 1;
  }

  printf("Reading contents:\n");

  fp = fopen(filename, "r");
  if (fp == NULL) {
    perror("Error opening file for reading");
    return 1;
  }

  while (fgets(line, sizeof(line), fp) != NULL) {
    printf("%s", line);
    lines_read++;
  }

  if (ferror(fp)) {
    perror("Error reading file");
    fclose(fp);
    return 1;
  }

  if (fclose(fp) != 0) {
    perror("Error closing file");
    return 1;
  }

  printf("Lines read: %d\n", lines_read);

  return 0;
}
