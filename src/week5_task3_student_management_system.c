/*Lab 5, Task 2
  Name: <Murshid Gasimov>
  Student ID: <251ADB074>*/
  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STUDENTS 100

typedef struct
{
    char name[50];
    int id;
    float gpa;
} Student;

void read_line(char *buffer, size_t size)
{
    if (fgets(buffer, (int)size, stdin) == NULL)
    {
        buffer[0] = '\0';
        return;
    }

    size_t len = strlen(buffer);

    if (len > 0 && buffer[len - 1] == '\n')
    {
        buffer[len - 1] = '\0';
    }
    else
    {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF)
        {
        }
    }
}

int load_students(Student arr[], int max)
{
    FILE *fp = fopen("students.txt", "r");

    if (fp == NULL)
    {
        return 0;
    }

    char line[256];
    int count = 0;

    while (count < max && fgets(line, sizeof(line), fp) != NULL)
    {
        char name[50];
        int id;
        float gpa;
        char extra;

        if (sscanf(line, " %49[^,],%d,%f %c",
                   name, &id, &gpa, &extra) != 3)
        {
            continue;
        }

        size_t len = strlen(name);

        while (len > 0 && isspace((unsigned char)name[len - 1]))
        {
            name[--len] = '\0';
        }

        char *start = name;
        while (isspace((unsigned char)*start))
        {
            start++;
        }

        if (*start == '\0' || id <= 0 ||
            gpa < 0.0f || gpa > 4.0f)
        {
            continue;
        }

        if (start != name)
        {
            memmove(name, start, strlen(start) + 1);
        }

        strcpy(arr[count].name, name);
        arr[count].id = id;
        arr[count].gpa = gpa;
        count++;
    }

    fclose(fp);
    return count;
}

int save_students(const Student arr[], int count)
{
    FILE *fp = fopen("students.txt", "w");

    if (fp == NULL)
    {
        perror("Error opening students.txt");
        return -1;
    }

    for (int i = 0; i < count; i++)
    {
        if (fprintf(fp, "%s,%d,%.2f\n",
                    arr[i].name, arr[i].id, arr[i].gpa) < 0)
        {
            fclose(fp);
            return -1;
        }
    }

    if (fclose(fp) != 0)
    {
        return -1;
    }

    return 0;
}

void add_student(Student arr[], int *count)
{
    char name[256];
    char input[100];
    char *end;
    long id;
    float gpa;

    if (*count >= MAX_STUDENTS)
    {
        printf("Cannot add more students (limit reached).\n");
        return;
    }

    printf("Enter name: ");
    read_line(name, sizeof(name));

    printf("Enter ID: ");
    read_line(input, sizeof(input));

    if (input[0] == '\0')
    {
        printf("Invalid input. Student not added.\n");
        return;
    }

    id = strtol(input, &end, 10);

    while (isspace((unsigned char)*end))
    {
        end++;
    }

    if (end == input || *end != '\0' || id <= 0 ||
        id > 2147483647L)
    {
        printf("Invalid input. Student not added.\n");
        return;
    }

    printf("Enter GPA: ");
    read_line(input, sizeof(input));

    if (input[0] == '\0')
    {
        printf("Invalid input. Student not added.\n");
        return;
    }

    gpa = strtof(input, &end);

    while (isspace((unsigned char)*end))
    {
        end++;
    }

    if (end == input || *end != '\0' ||
        gpa < 0.0f || gpa > 4.0f)
    {
        printf("Invalid input. Student not added.\n");
        return;
    }

    size_t len = strlen(name);

    while (len > 0 && isspace((unsigned char)name[len - 1]))
    {
        name[--len] = '\0';
    }

    char *start = name;

    while (isspace((unsigned char)*start))
    {
        start++;
    }

    if (*start == '\0' || strchr(name, ',') != NULL ||
        strlen(start) >= sizeof(arr[*count].name))
    {
        printf("Invalid input. Student not added.\n");
        return;
    }

    memmove(name, start, strlen(start) + 1);

    strcpy(arr[*count].name, name);
    arr[*count].id = (int)id;
    arr[*count].gpa = gpa;
    (*count)++;

    printf("Student added successfully!\n");
}

void list_students(const Student arr[], int count)
{
    if (count == 0)
    {
        printf("No students found.\n");
        return;
    }

    printf("%-6s %-20s GPA\n", "ID", "Name");

    for (int i = 0; i < count; i++)
    {
        printf("%-6d %-20s %.2f\n",
               arr[i].id, arr[i].name, arr[i].gpa);
    }
}

int main(void)
{
    Student students[MAX_STUDENTS] = {0};
    int count = load_students(students, MAX_STUDENTS);

    printf("Loaded %d student(s) from students.txt\n", count);

    char input[100];
    char *end;
    long option;

    while (1)
    {
        printf("\n=== Student Management System ===\n");
        printf("1. List students\n");
        printf("2. Add student\n");
        printf("3. Save and Exit\n");
        printf("Select an option: ");

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            break;
        }

        option = strtol(input, &end, 10);

        while (isspace((unsigned char)*end))
        {
            end++;
        }

        if (end == input || *end != '\0')
        {
            printf("Invalid option.\n");
            continue;
        }

        if (option == 1)
        {
            list_students(students, count);
        }
        else if (option == 2)
        {
            add_student(students, &count);
        }
        else if (option == 3)
        {
            break;
        }
        else
        {
            printf("Invalid option.\n");
        }
    }

    if (save_students(students, count) != 0)
    {
        fprintf(stderr, "Error saving student data.\n");
        return 1;
    }

    printf("Data saved. Goodbye!\n");
    return 0;
}
