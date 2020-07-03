/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** params.c
*/

#include "../include/my.h"

params_t register_param(params_t params, char *argument)
{
    int number = 0;

    params.label = false;
    number = my_getnbr(&argument[1]);
    if (number <= 0 || number > REG_NUMBER)
        exit (84);
    params.bytes_size = 1;
    params.binary = "01";
    params.type = 1;
    return (params);
}

params_t direct_param(params_t params, char *argument, args_t args)
{
    int number = 0;
    char *tab[6] = {"zjmp", "ldi", "sti", "fork", "lldi", "lfork"};

    number = my_getnbr(&argument[1]);
    params.label = false;
    params.bytes_size = DIR_SIZE;
    params.binary = "10";
    params.type = 2;
    for (int j = 0; j < 6; j += 1)
        if (!my_strcmp(tab[j], args.instruction))
            params.bytes_size = 2;
    if (number > 0 || argument[1] == '0' || number < 0)
        return (params);
    if (argument[1] != LABEL_CHAR)
        exit (84);
    params.label = true;
    return (params);
}

params_t indirect_param(params_t params, char *argument)
{
    int number = 0;

    number = my_getnbr(&argument[0]);
    params.label = false;
    params.bytes_size = IND_SIZE;
    params.binary = "11";
    params.type = 3;
    if (number > 0 || number < 0)
        return (params);
    if (argument[0] != LABEL_CHAR)
        exit (84);
    params.label = true;
    return (params);
}