/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** exec_sti.c
*/

#include "../include/my.h"

int find_arg(machine_t *machine, champion_t *champion, \
coding_t coding, char *binary)
{
    int result = 0;
    int temp_pc = 0;

    coding.pc = coding.pc % MEM_SIZE;
    result = get_good_number(machine, coding.pc, 2);
    if (binary[coding.index] == '1' && binary[coding.index + 1] == '0') {
        return (result);
    } else if (binary[coding.index] == '1') {
        temp_pc = (champion->pc + result) % MEM_SIZE;
        result = get_good_number(machine, temp_pc, 2);
        return (result);
    }
    result = get_good_number(machine, coding.pc, 1) - 1;
    if (result < 0 || result > REG_NUMBER - 1)
        return (0);
    result = calc_register(champion->registers[result]);
    return (result);
}

void final_sti(machine_t *machine, champion_t *champion, \
int good_adress, int check[2])
{
    check[0] = good_adress % MEM_SIZE;
    if (check[0] < 0)
        check[0] = MEM_SIZE + check[0];
    for (int i = 0; i < REG_SIZE; check[0] += 1) {
        if (check[0] >= MEM_SIZE)
            check[0] = 0;
        machine->memory[check[0]] = \
        champion->registers[check[1]][i];
        machine->grid[check[0]].c = \
        champion->registers[check[1]][i];
        machine->grid[check[0]].color = champion->color;
        i += 1;
    }
}

void sti_next(machine_t *machine, champion_t *champion, \
int tmp[2], int check[4])
{
    int good_adress = (champion->pc + \
    (check[2] + check[3]) % IDX_MOD) % MEM_SIZE;

    final_sti(machine, champion, good_adress, tmp);
}

void exec_sti(machine_t *machine, champion_t *champion)
{
    char *binary = find_coding_byte(machine, champion);
    int tmp[2] = {champion->pc, \
    champion->pc};
    int reg = 0;
    int args[2] = {0, 0};
    int check[4] = {0, 0, 0, 0};

    if (nb_params(binary) != 3 || binary[0] != '0' || binary[1] != '1')
        return (update_easy_pc(champion));
    tmp[1] = (tmp[1] + 2) % MEM_SIZE;
    reg = machine->grid[tmp[1]].c - 1;
    if (reg < 0 || reg > REG_NUMBER - 1)
        return (update_easy_pc(champion));
    args[0] = find_arg(machine, champion, (coding_t){2, tmp[1] + 1}, binary);
    tmp[1] += (binary[2] == '0') ? 2 : 3;
    args[1] = find_arg(machine, champion, (coding_t){4, tmp[1]}, binary);
    check[2] = args[0];
    check[3] = args[1];
    tmp[1] = reg;
    sti_next(machine, champion, tmp, check);
    wrong_parameters(machine, champion, binary, true);
}