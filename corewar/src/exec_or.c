/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** exec_live.c
*/

#include "../include/my.h"

void write_in_regist(int args[3], champion_t *champion)
{
    int result = result = args[0] | args[1];

    if (args[2] < 0 || args[2] > REG_NUMBER - 1)
        return;
    if (result == 0)
        champion->carry = 1;
    else
        champion->carry = 0;
    champion->registers[args[2]][0] = (result >> 24) & 0xFF;
    champion->registers[args[2]][1] = (result >> 16) & 0xFF;
    champion->registers[args[2]][2] = (result >> 8) & 0xFF;
    champion->registers[args[2]][3] = result & 0xFF;
}

void exec_or(machine_t *machine, champion_t *champion)
{
    char *binary = find_coding_byte(machine, champion);
    int good_pc = champion->pc + 2;
    int args[3] = {0, 0, 0};

    if (nb_params(binary) != 3 || binary[4] == '1')
        return (update_easy_pc(champion));
    args[0] = find_argument(machine, champion, binary, (coding_t){0, good_pc});
    good_pc += (binary[0] == '1' && binary[1] == '0') ? 4 : \
    (binary[0] == '0') ? 1 : 2;
    good_pc = good_pc % MEM_SIZE;
    args[1] = find_argument(machine, champion, binary, (coding_t){2, good_pc});
    good_pc += (binary[2] == '1' && binary[3] == '0') ? 4 : \
    (binary[2] == '0') ? 1 : 2;
    good_pc = good_pc % MEM_SIZE;
    args[2] = get_good_number(machine, good_pc, T_REG) - 1;
    write_in_regist(args, champion);
    wrong_parameters(machine, champion, binary, false);
}