#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILENAME "input"
#define BUFFER_SIZE 1024

#define CMD_EXAMPLE "example"
#define CMD_SOLVE "solve"

// solve
void run_program(int *arr, size_t size);

// commands
void c_example(char part, char *input);
void c_solve(char part);

// parse
void parse_input(char *input, int *arr, size_t *size);

// helper
void print_arr_int(int *arr, size_t size);

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

void run_program(int *arr, size_t size) {
  int opcode = 0;

  for (size_t i = 0; i < size; i += 4) {
    opcode = arr[i];

    if (opcode == 1)
      arr[arr[i + 3]] = arr[arr[i + 1]] + arr[arr[i + 2]];
    else if (opcode == 2)
      arr[arr[i + 3]] = arr[arr[i + 1]] * arr[arr[i + 2]];
    else if (opcode == 99)
      break;
    else {
      fprintf(stderr, "ERROR: found opcode %d in position %zu\n", opcode, i);
      break;
    }
  }
}

/* --------
   commands
   -------- */

void c_example(char part, char *input) {
  int arr[BUFFER_SIZE] = {0};
  size_t size = 0;
  parse_input(input, arr, &size);

  if (part == '1') {
    run_program(arr, size);
    print_arr_int(arr, size);
  } else if (part == '2')
    printf("Nothing to do\n");
  else {
    fprintf(stderr, "ERROR: unrecognised part %c\n", part);
    printf("Choose between part 1 or 2\n");
    return;
  }
}

void c_solve(char part) {
  FILE *fp = fopen(INPUT_FILENAME, "r");
  if (!fp) {
    fprintf(stderr, "ERROR: could not open file %s\n", INPUT_FILENAME);
    return;
  }

  char buffer[BUFFER_SIZE];
  fgets(buffer, BUFFER_SIZE, fp);

  fclose(fp);

  int arr[BUFFER_SIZE] = {0};
  size_t size = 0;
  parse_input(buffer, arr, &size);

  if (part == '1') {
    arr[1] = 12;
    arr[2] = 2;

    run_program(arr, size);

    printf("%d\n", arr[0]);
  } else if (part == '2') {
    int arr_tmp[BUFFER_SIZE] = {0};
    for (int noun = 0; noun < 100; noun++) {
      for (int verb = 0; verb < 100; verb++) {
        // initialize
        memcpy(arr_tmp, arr, size*sizeof(int));
        arr_tmp[1] = noun;
        arr_tmp[2] = verb;

        // run
        run_program(arr_tmp, size);
        if (arr_tmp[0] == 19690720) {
          printf("%d\n", 100 * noun + verb);
          return;
        }
      }
    }

  } else {
    fprintf(stderr, "ERROR: unrecognised part %c\n", part);
    printf("Choose between part 1 or 2\n");
    return;
  }
}

/* -----
   parse
   ----- */

void parse_input(char *input, int *arr, size_t *size) {
  int tmp = 0;
  int tmp_size = 0;

  for (int i = 0; input[i] != '\0' && input[i] != '\n'; i++) {
    if (input[i] == ',') {
      arr[tmp_size] = tmp;
      tmp_size++;
      tmp = 0;
      continue;
    }
    tmp = 10 * tmp + input[i] - '0';
  }

  arr[tmp_size] = tmp;
  *size = tmp_size + 1;
}

/* -------
   helpers
   ------- */

void print_arr_int(int *arr, size_t size) {
  for (size_t i = 0; i < size - 1; i++)
    printf("%d ", arr[i]);
  printf("%d\n", arr[size - 1]);
}
