/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** exec_lfork.c
*/

#include "../include/my.h"

void exec_lfork(machine_t *machine, champion_t *champion)
{
    int good_pc = (champion->pc + 1) % MEM_SIZE;
    int number = get_good_number(machine, good_pc, 2);
    int new_address = ((good_pc - 1) + number) % MEM_SIZE;

    add_champion(&champion, new_address);
    champion->pc += 3;
}