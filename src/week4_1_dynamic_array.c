/*Lab 4, Task 1
  Name: <Murshid Gasimov>
  Student ID: <251ADB074>*/

#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int n;

  printf("Enter number of elements: ");

  if (scanf("%d", &n) != 1 || n <= 0) {
    printf("Invalid size.\n");
    return 1;
  }

  int* numbers = malloc(n * sizeof(int));

  if (numbers == NULL) {
    printf("Memory allocation failed.\n");
    return 1;
  }

  printf("Enter %d integers: ", n);

  int sum = 0;

  for (int i = 0; i < n; i++) {
    if (scanf("%d", &numbers[i]) != 1) {
      printf("Invalid input.\n");
      free(numbers);
      return 1;
    }

    sum += numbers[i];
  }

  double average = (double)sum / n;

  printf("Sum = %d\n", sum);
  printf("Average = %.2f\n", average);

  free(numbers);

  return 0;
}