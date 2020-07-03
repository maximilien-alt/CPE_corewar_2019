/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** exec_live.c
*/

#include "../include/my.h"

void exec_direct(machine_t *machine, champion_t *champion, \
int good_pc, int reg)
{
    int result = get_good_number(machine, good_pc, 4);

    if (result == 0)
        champion->carry = 1;
    else
        champion->carry = 0;
    for (int i = 0; i < REG_SIZE; i += 1) {
        champion->registers[reg][i] = \
        machine->grid[good_pc].c;
        good_pc = (good_pc + 1) % MEM_SIZE;
    }
}

void exec_indirect(machine_t *machine, \
champion_t *champion, int good_pc, int check[2])
{
    int result = get_good_number(machine, good_pc, 2);
    int adress_pc = (champion->pc + result % IDX_MOD) % MEM_SIZE;

    if (result == 0)
        champion->carry = 1;
    else
        champion->carry = 0;
    for (int i = 0; i < REG_SIZE; i += 1) {
        champion->registers[check[0]][i] = \
        machine->grid[adress_pc].c;
        adress_pc += 1;
        if (adress_pc >= MEM_SIZE)
            adress_pc = 0;
    }
}

int get_good_pc(char *binary, int good_pc)
{
    if (binary[0] == '1' && binary[1] == '0')
        good_pc = (good_pc + 2 + REG_SIZE) % MEM_SIZE;
    else
        good_pc = (good_pc + 2 + IND_SIZE) % MEM_SIZE;
    return (good_pc);
}

void update_easy_pc(champion_t *champion)
{
    champion->pc = (champion->pc + 1) % MEM_SIZE;
}

void exec_ld(machine_t *machine, champion_t *champion)
{
    char *binary = find_coding_byte(machine, champion);
    int good_pc = champion->pc;
    int reg = 0;
    int check[2] = {0, 0};

    if (nb_params(binary) != 2 || binary[0] == '0' || binary[2] == '1')
        return (update_easy_pc(champion));
    good_pc = get_good_pc(binary, good_pc);
    reg = get_good_number(machine, good_pc, T_REG) - 1;
    if (reg < 0 || reg > REG_NUMBER - 1)
        return (update_easy_pc(champion));
    good_pc = (champion->pc + 2) % MEM_SIZE;
    if (binary[0] == '1' && binary[1] == '0')
        exec_direct(machine, champion, good_pc, reg);
    else {
        check[0] = reg;
        exec_indirect(machine, champion, good_pc, check);
    }
    wrong_parameters(machine, champion, binary, false);
}