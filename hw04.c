#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    NAME_ONLY = 0,
    MAJOR_AND_NAME = 1,
    YEAR_AND_NAME = 2,
    YEARS_LEFT_AND_NAME=3
} Mode;

typedef struct {
    char *first_name;
    char *last_name;
    char *major;
    int year;
} Student;

void print_student(Mode m, Student s) {
    switch (m) {
            int years_left;
        case NAME_ONLY:
            printf("%s %s\n", s.first_name, s.last_name);
            break;
        case MAJOR_AND_NAME:
            printf("%s %s %s\n",s.major, s.first_name, s.last_name);
            break;
        case YEAR_AND_NAME:
            printf("%d %s %s\n", s.year, s.first_name, s.last_name);
            break;
        case YEARS_LEFT_AND_NAME:
            years_left = s.year - 2017;
            printf("%d %s %s\n", years_left, s.first_name, s.last_name);
            break;
        default:
            printf("Incorrect Format\n");
            break;
        }
}

int main(int argc, char *argv[]) {
  Student stu[256];
  char *filename = argv[1];
  FILE *fp = fopen(filename, "r");
  char buffer[256];
  char *string_array[256];
  
  if (fp == NULL) {
    printf("Could not open %s\n", filename);
    return -1;
  }

  // read one line at a time
  char *t;
  int i = 0;
  
  // First loop to process input file
  while ((t = fgets(buffer, 255, fp)) != NULL) {
    //printf("Buffer: %s", buffer);
	size_t len = strlen(buffer);
	size_t len_bytes = (len + 1) * sizeof(char);
	char *new_string = malloc(len_bytes);
    memcpy(new_string, buffer, len_bytes);
    Student s;
    s.first_name = malloc(len_bytes);
    s.last_name = malloc(len_bytes);
    s.major = malloc(len_bytes);
    sscanf(buffer, "%s %s %s %d", s.first_name, s.last_name, s.major, &s.year);
    stu[i] = s;
    i++;
	
  }
  while(1) {
    int index, mode;
    fscanf(stdin, "%d %d", &index, &mode);
    print_student(mode, stu[index]);
    }
  /* Second loop to access data array
  for (int j = 0; j < i; j++) {
	printf("string_array[j]: %s", string_array[j]);  
  }
  */
  // Final loop to clean up memory
  for (int j = 0; j < i; j++) {
	if (stu[j].first_name != NULL)
	  free(stu[j].first_name);
    if (stu[j].last_name != NULL)
      free(stu[j].last_name);
    if (stu[j].major != NULL)
      free(stu[j].major);
	
  }
 
  fclose(fp);
  return 0;

}
