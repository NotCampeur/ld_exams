#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "get_next_line.h"

__attribute__ ((destructor)) void ft_leave(void)
{
	system("leaks a.out");
}

int main() {
    int ret;
    char *line;

    line = 0;
    ret = get_next_line(&line);
    while (ret > 0) {
        write(1, line, strlen(line));
        write(1, "\n", 1);
        free(line);
        line = 0;
        ret = get_next_line(&line);
    }
    if (ret == 0) {
        write(1, line, strlen(line));
        write(1, "\n", 1);
        free(line);
        line = 0;
    }
}
