#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"
#include "get_next_line_bonus.h"

void	test_file(const char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf("Error:Failed to open file %s\n", filename);
		return ;
	}
	printf("\nTesting file: %s\n", filename);
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("Line:%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

int	main(void)
{
	// Test 1: Empty file
	test_file("t_empty.txt");
	// Test 2: File with just a newline
	test_file("t_newline.txt");
	// Test 3: File with "Hello World"
	test_file("t_hello_world.txt");
	// Test 4: File with multiple newlines between "Hello World"
	test_file("t_mult_newlines.txt");
	return (0);
}
