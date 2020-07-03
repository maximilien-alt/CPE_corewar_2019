/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** exec_aff.c
*/

#include "../include/my.h"

int reg_to_int(char *str, int size)
{
    int number = 0;

    for (int j = 0; j < size; j += 1) {
        number = (number << 8);
        number += str[j];
    }
    return (number);
}

void exec_aff(machine_t *machine, champion_t *champion)
{
    char *binary = find_coding_byte(machine, champion);
    int reg = 0;
    int good_pc = champion->pc;

    if (nb_params(binary) != 1 || binary[0] == '1')
        return (update_easy_pc(champion));
    reg = get_good_number(machine, good_pc + 2, T_REG) - 1;
    if (reg < 0 || reg > REG_NUMBER - 1) {
        champion->pc = \
        (champion->pc + 3) % MEM_SIZE;
        return;
    }
    my_printf("%c", \
    reg_to_int(champion->registers[reg], 4) % 256);
    champion->pc = (champion->pc + 3) % MEM_SIZE;
}