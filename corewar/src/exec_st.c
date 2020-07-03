/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** exec_live.c
*/

#include "../include/my.h"

void st_register(machine_t *machine, int good_pc, \
int check[2], champion_t *champion)
{
    int temp = get_good_number(machine, good_pc + 1, 1);

    if (temp < 0 || temp > REG_NUMBER - 1) {
        champion->pc = (champion->pc + 4) % MEM_SIZE;
        return;
    }
    for (int i = 0; i < REG_SIZE; i += 1)
        champion->registers[temp][i] = \
        champion->registers[check[0]][i];
    champion->pc = (champion->pc + 4) % MEM_SIZE;
}

void st_number(machine_t *machine, int good_pc, \
int check[2], champion_t *champion)
{
    int temp = get_good_number(machine, good_pc + 1, 2);
    int good_adress = (champion->pc + temp % IDX_MOD) % MEM_SIZE;

    for (int i = 0; i < REG_SIZE; i += 1) {
        machine->memory[good_adress] = champion->registers[check[0]][i];
        machine->grid[good_adress].c = \
        champion->registers[check[0]][i];
        machine->grid[good_adress].color = champion->color;
        good_adress += 1;
        if (good_adress >= MEM_SIZE)
            good_adress = 0;
    }
    champion->pc = (champion->pc + 5) % MEM_SIZE;
}

void exec_st(machine_t *machine, champion_t *champion)
{
    char *binary = find_coding_byte(machine, champion);
    int good_pc = champion->pc + 2;
    int reg = 0;
    int check[2] = {0, 0};

    if (nb_params(binary) != 2 || binary[0] == '1' || \
    (binary[2] == '1' && binary[3] == '0'))
        return (update_easy_pc(champion));
    reg = get_good_number(machine, good_pc, T_REG) - 1;
    if (reg < 0 || reg > REG_NUMBER - 1)
        return (update_easy_pc(champion));
    check[0] = reg;
    if (binary[2] == '0')
        st_register(machine, good_pc, check, champion);
    else
        st_number(machine, good_pc, check, champion);
}