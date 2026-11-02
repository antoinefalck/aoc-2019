#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILENAME "input"
#define BUFFER_SIZE 128

#define CMD_EXAMPLE "example"
#define CMD_SOLVE "solve"

// solve
int get_fuel(int mass);
int get_fuel_full(int mass);

// commands
void c_example(char part, char *input);
void c_solve(char part);

int main(int argc, char **argv) {
  if (argc == 1) {
    fprintf(stderr, "ERROR: no command provided\n");
    printf("Usage: ./main <command>\n");
    return 1;
  }

  char *command = argv[1];
  if (strncmp(command, CMD_EXAMPLE, strlen(CMD_EXAMPLE)) == 0) {
    char part = command[strlen(CMD_EXAMPLE)];
    if (part != '1' && part != '2') {
      fprintf(stderr, "ERROR: unrecognised part %c\n", part);
      printf("Choose between part 1 or 2\nUsage: ./main %s[1|2] <input>\n",
             CMD_EXAMPLE);
      return 1;
    }
    if (argc < 3) {
      fprintf(stderr, "ERROR: no input provided\n");
      printf("Usage: ./main %s%c <input>\n", CMD_EXAMPLE, part);
      return 1;
    }
    c_example(part, argv[2]);
  } else if (strncmp(command, CMD_SOLVE, strlen(CMD_SOLVE)) == 0) {
    char part = command[strlen(CMD_SOLVE)];
    if (part != '1' && part != '2') {
      fprintf(stderr, "ERROR: unrecognised part %c\n", part);
      printf("Choose between part 1 or 2\nUsage: ./main %s[1|2] <input>\n",
             CMD_SOLVE);
      return 1;
    }
    c_solve(part);
  } else {
    fprintf(stderr, "ERROR: unrecognised command %s\n", command);
    return 1;
  }

  return 0;
}

/* -----
   solve
   ----- */

// part 1
int get_fuel(int mass) { return mass / 3 - 2; }

// part 2
int get_fuel_full(int mass) {
  int res = 0;

  for (int tmp = get_fuel(mass); tmp > 0; tmp = get_fuel(tmp))
    res += tmp;

  return res;
}

/* --------
   commands
   -------- */

void c_example(char part, char *input) {
  int res;
  if (part == '1')
    res = get_fuel(atoi(input));
  else if (part == '2')
    res = get_fuel_full(atoi(input));
  else {
    fprintf(stderr, "ERROR: unrecognised part %d\n", part);
    printf("Choose between part 1 or 2\n");
    return;
  }

  printf("%d\n", res);
}

void c_solve(char part) {
  // get function part 1 or 2
  int (*f)(int);
  if (part == '1')
    f = get_fuel;
  else if (part == '2')
    f = get_fuel_full;
  else {
    fprintf(stderr, "ERROR: unrecognised part %c\n", part);
    printf("Choose between part 1 or 2\n");
    return;
  }

  FILE *fp = fopen(INPUT_FILENAME, "r");
  if (!fp) {
    fprintf(stderr, "ERROR: could not open file %s\n", INPUT_FILENAME);
    return;
  }

  int res = 0;
  char buffer[BUFFER_SIZE];
  while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
    res += f(atoi(buffer));
  }

  fclose(fp);

  printf("%d\n", res);
}

/* -------
   helpers
   ------- */
