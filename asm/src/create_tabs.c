/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** create_tabs.c
*/

#include "../include/my.h"

void fill_tabs(nodes_t *nodes, int index)
{
    for (int check = 0; nodes->args[check]; index += 1) {
        if (nodes->params[check].type == -1)
            return;
        if (nodes->params[check].type == 2 || nodes->params[check].type == 1)
            nodes->to_write[index] = \
            my_getnbr(&nodes->params[check].parameter[1]);
        if (nodes->params[check].type == 3)
            nodes->to_write[index] = \
            my_getnbr(&nodes->params[check].parameter[0]);
        nodes->bytes_stack[index] = nodes->params[check].bytes_size;
        check += 1;
    }
}

int my_binary_to_int(char *str)
{
    int result = 0;
    int pow = 1;

    for (int len = my_strlen(str) - 1; len >= 0; len -= 1) {
        result += (str[len] - '0') * pow;
        pow *= 2;
    }
    return (result);
}

void complete_tabs(nodes_t *nodes, int check, char *str, int j)
{
    int index = 1;

    if (!check) {
        str = my_malloc(sizeof(char) * 9);
        str[8] = 0;
        my_memset(str, '0', 8);
        for (int temp = 0; nodes->args[temp] && \
        nodes->params[temp].type != -1; temp += 1) {
            str[j] = nodes->params[temp].binary[0];
            str[j + 1] = nodes->params[temp].binary[1];
            j += 2;
        }
        nodes->to_write[index] = my_binary_to_int(str);
        nodes->bytes_stack[index] = 1;
        index += 1;
    }
    fill_tabs(nodes, index);
}

void init_tabs(nodes_t *nodes, int malloc_size)
{
    nodes->to_write = my_malloc(sizeof(int) * malloc_size);
    nodes->bytes_stack = my_malloc(sizeof(int) * malloc_size);
    for (int index = 0; index < malloc_size; index += 1) {
        nodes->to_write[index] = -1;
        nodes->bytes_stack[index] = -1;
    }
}

void create_tabs(nodes_t *nodes, int check, args_t args)
{
    char *tab[4] = {"live", "zjmp", "fork", "lfork"};
    int malloc_size = nodes->nbr_args + 3;

    nodes->params = check_params(args);
    if (!nodes->params)
        return;
    for (int i = 0; i < 4; i += 1)
        if (!my_strcmp(tab[i], nodes->instruction)) {
            malloc_size -= 1;
            check += 1;
            nodes->coding_byte = false;
        }
    init_tabs(nodes, malloc_size);
    for (int index = 0; index < 16; index += 1)
        if (!my_strcmp(nodes->instruction, op_tab[index].mnemonique))
            nodes->to_write[0] = op_tab[index].code;
    nodes->bytes_stack[0] = 1;
    if (nodes->to_write[0] == -1)
        exit (84);
    complete_tabs(nodes, check, NULL, 0);
}