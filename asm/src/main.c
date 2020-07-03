/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** asm_main.c
*/

#include "../include/my.h"

int main(int ac, char *av[])
{
    char *buffer = NULL;
    char **tab = NULL;
    int ret = 0;

    if (ac != 2)
        return (84);
    if (!my_strcmp(av[1], "-h"))
        display_usage();
    buffer = read_file(av[1]);
    if (!buffer)
        return (84);
    tab = my_str_to_word_array(buffer, "\n");
    if (!tab)
        return (84);
    ret = create_champion(tab, av[1]);
    return (ret);
}