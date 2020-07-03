/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** exec_live.c
*/

#include "../include/my.h"

int calc_register(char *reg)
{
    int result = 0;
    int check = reg[0];

    for (int index = 0; index < REG_SIZE; index += 1) {
        result = result << 8;
        if (index != 0 && reg[index] < 0 && check == -1)
            return (reg[index]);
        result += reg[index];
    }
    return ((unsigned char)result == 0 ? result : (unsigned char)result);
}

void calc_add(champion_t *champion, int regs[3])
{
    int numbers[2] = {0, 0};
    int result = 0;

    for (int i = 0; i < 2; i += 1)
        numbers[i] = \
        calc_register(champion->registers[regs[i]]);
    result = numbers[0] + numbers[1];
    if (result == 0)
        champion->carry = 1;
    else
        champion->carry = 0;
    champion->registers[regs[2]][0] = \
    (result >> 24) & 0xFF;
    champion->registers[regs[2]][1] = \
    (result >> 16) & 0xFF;
    champion->registers[regs[2]][2] = \
    (result >> 8) & 0xFF;
    champion->registers[regs[2]][3] = result & 0xFF;
    champion->pc = \
    (champion->pc + 5) % MEM_SIZE;
}

void exec_add(machine_t *machine, champion_t *champion)
{
    char *binary = find_coding_byte(machine, champion);
    int regs[3] = {0, 0, 0};
    int good_pc = champion->pc + 2;

    if (nb_params(binary) != 3 || binary[0] == '1' || \
    binary[2] == '1' || binary[4] == '1')
        return (update_easy_pc(champion));
    regs[0] = get_good_number(machine, good_pc, T_REG) - 1;
    regs[1] = get_good_number(machine, good_pc + 1, T_REG) - 1;
    regs[2] = get_good_number(machine, good_pc + 2, T_REG) - 1;
    for (int i = 0; i < 3; i += 1)
        if (regs[i] < 0 || regs[i] > REG_NUMBER - 1)
            return (update_easy_pc(champion));
    calc_add(champion, regs);
}