/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** reading.c
*/

#include "../include/my.h"

void display_usage(void)
{
    my_printf("USAGE\n\
    ./asm file_name[.s]\n\
\nDESCRIPTION\n\
    file_name   \
    file in assembly language to be converted into file_name.cor, an\n\
                    executable in the Virtual Machine.\n");
}

char *read_file(char *filepath)
{
    FILE *fd = fopen(filepath, "r");
    char *buffer = NULL;
    size_t size = 0;
    char *temp = NULL;
    int check = 0;

    if (!fd)
        return (NULL);
    while (getline(&buffer, &size, fd) != -1) {
        temp = my_strcat(temp, buffer);
        check += 1;
    }
    if (!buffer || check == 1)
        return (NULL);
    return (temp);
}