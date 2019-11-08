#include <stdio.h>
#include <stdlib.h>
#include <string.h> // required for strchr()

int main(int argc, char **argv)
{
	if (argc != 2) {
		printf("please specify a file.");
		exit(EXIT_FAILURE);
	}

	FILE *stream = fopen(argv[1], "r");
	if (stream == NULL)
		exit(EXIT_FAILURE);
	
	char **linesArray = NULL;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	size_t i = 0;
	while ((read = getline(&line, &len, stream)) != -1) {
		char **tmp = realloc(linesArray, sizeof(*linesArray) * (i + 1));
		if (!tmp) {
			perror("realloc failure.");
			return EXIT_FAILURE;
		}
		linesArray = tmp;
		// Remove trailing newline
		line[strcspn(line, "\n")] = 0;
		*(linesArray + i) = line;

		// line is not freed, so memory allocated for the string
		// collected by getline() is intact.
		//
		// We set `line` to NULL so that getline can use it again.
		// Because line is set to NULL, getline will dynamically allocate
		// a fresh memory buffer to store the line if we go round the
		// loop again.
		line = NULL;
		i++;
	}
	free(line);
	fclose(stream);
	
	for (size_t j = 0; j < i; j++) {
		printf("Line %lu: %s\n", j, linesArray[j]);
		free(linesArray[j]);
	}
	free(linesArray);
	exit(EXIT_SUCCESS);
}

