/*
** EPITECH PROJECT, 2019
** asm
** File description:
** check_error.c
*/

#include "../include/my.h"

void check_live(nodes_t *nodes)
{
    if (nodes->nbr_args != 1 || nodes->bytes_stack[1] != 4)
        exit (84);
}

void check_ld(nodes_t *nodes)
{
    if (nodes->nbr_args != 2 || nodes->bytes_stack[3] != T_REG)
        exit (84);
}

void check_st(nodes_t *nodes)
{
    if (nodes->nbr_args != 2 || nodes->bytes_stack[2] != T_REG)
        exit (84);
}

void check_add(nodes_t *nodes)
{
    if (nodes->nbr_args != 3)
        exit (84);
    for (int i = 2; i <= 4; i += 1)
        if (nodes->bytes_stack[i] != T_REG)
            exit (84);
}

void check_aff(nodes_t *nodes)
{
    if (nodes->nbr_args != 1 || nodes->bytes_stack[2] != T_REG)
        exit (84);
}