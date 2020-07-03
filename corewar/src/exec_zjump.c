/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** exec_zjump.c
*/

#include "../include/my.h"

void exec_zjump(machine_t *machine, champion_t *champion)
{
    int result = 0;
    int good_pc = champion->pc;

    if (champion->carry == 0) {
        champion->pc = \
        (champion->pc + IND_SIZE + 1) % MEM_SIZE;
        return;
    }
    result = get_good_number(machine, good_pc + 1, IND_SIZE);
    champion->pc = \
    (champion->pc + result % IDX_MOD) % MEM_SIZE;
    if (champion->pc < 0)
        champion->pc = MEM_SIZE + \
        champion->pc;
}