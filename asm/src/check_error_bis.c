/*
** EPITECH PROJECT, 2019
** asm
** File description:
** check_error_bis.c
*/

#include "../include/my.h"

void check_and(nodes_t *nodes)
{
    if (nodes->nbr_args != 3 || nodes->bytes_stack[4] != T_REG)
        exit (84);
}

void check_zjmp(nodes_t *nodes)
{
    if (nodes->nbr_args != 1 || nodes->bytes_stack[1] == T_REG)
        exit (84);
}

void check_ldi(nodes_t *nodes)
{
    if (nodes->nbr_args != 3 || nodes->bytes_stack[4] != T_REG)
        exit (84);
}

void check_sti(nodes_t *nodes)
{
    if (nodes->nbr_args != 3 || nodes->bytes_stack[2] != T_REG)
        exit (84);
}

void check_fork(nodes_t *nodes)
{
    if (nodes->nbr_args != 1 || nodes->bytes_stack[1] == T_REG)
        exit (84);
}