Read a line from stdin in C: getline()
======================================
If you want to get a single line of `stdin` in C, `getline()` is the go-to function.

To get a single line from `stdin`:

```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  printf("Please enter a line:\n");
  char *line = NULL;
  size_t len = 0;
  ssize_t lineSize = 0;
  lineSize = getline(&line, &len, stdin);
  printf("You entered %s, which has %zu chars.\n", line, lineSize - 1);
  free(line);
  return 0;
}
```
Why do we have to `free(line)`? After all, there are no `malloc` family functions in the above code?

The answer is that `getline()` allocates memory to the buffer (in the example above, `line`) as required.

How Does getline() Work?
------------------------
`getline()` receives a pointer to a buffer in which to store the line string, a pointer to the size of the buffer, and a pointer to the input stream.

The function does the following:

* Allocates memory for the string buffer on the heap
* Updates the len variable to track the memory allocation
* Reads a line into the heap-allocated string buffer
* Returns the length of the string that has been read

Note that the newline character, not the null terminator, is counted in the length.

The memory allocated may be more than required for the input characters. If not enough memory is allocated initially, `getline()` can `realloc()` a longer buffer, while updating the `line` varible to point to the new buffer and updating `len`.

If `getline()` is called again, the original buffer is re-used unless reallocation of memory is required.

Example from `man getline`
-------------------------
The example in the man page loops through a file, collecting all lines into a single string. We can adapt this to read a file passed in as a command line argument:

```c 

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  if (argc != 2) {
    printf("please specify a file.");
    exit(EXIT_FAILURE);
  }
  FILE *stream;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  stream = fopen(argv[1], "r");
  if (stream == NULL)
    exit(EXIT_FAILURE);

  while ((read = getline(&line, &len, stream)) != -1) {
    printf("Retrieved line of length %zu :\n", read);
    printf("%s", line);
  }

  free(line);
  fclose(stream);
  exit(EXIT_SUCCESS);
}

```

References
----------
* [Courseera video, Duke Uni][1]: Reading a file with getline().
* [Code example][2]

[1]: https://www.coursera.org/lecture/interacting-system-managing-memory/reading-a-file-with-getline-Wk8aB
[2]: code
