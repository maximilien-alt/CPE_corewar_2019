/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** op.c
*/

#include "../include/op.h"
#include "../include/my.h"

void check_wrong_str(char *str)
{
    for (int index = 0; str[index]; index += 1) {
        if (str[index] != '"')
            continue;
        if (index > 0 && (str[index - 1] != ' ' && str[index - 1] != '\t'))
            exit (84);
        break;
    }
}

void wrong_line(nodes_t *node)
{
    for (int index = 0; index < 16; index += 1) {
        if (!node->instruction)
            continue;
        if (!my_strcmp(node->instruction, op_tab[index].mnemonique)) {
            op_tab[index].ptr(node);
            return;
        }
    }
}

op_t    op_tab[] =
{
    {"live", 1, {T_DIR}, 1, 10, "alive", check_live},
    {"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", check_ld},
    {"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", check_st},
    {"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", check_add},
    {"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", check_add},
    {"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
    "et (and  r1, r2, r3   r1&r2 -> r3", check_and},
    {"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
    "ou  (or   r1, r2, r3   r1 | r2 -> r3", check_and},
    {"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
    "ou (xor  r1, r2, r3   r1^r2 -> r3", check_and},
    {"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", check_zjmp},
    {"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
    "load index", check_ldi},
    {"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
    "store index", check_sti},
    {"fork", 1, {T_DIR}, 12, 800, "fork", check_fork},
    {"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", check_ld},
    {"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
    "long load index", check_ldi},
    {"lfork", 1, {T_DIR}, 15, 1000, "long fork", check_fork},
    {"aff", 1, {T_REG}, 16, 2, "aff", check_aff},
    {0, 0, {0}, 0, 0, 0, check_live}
};