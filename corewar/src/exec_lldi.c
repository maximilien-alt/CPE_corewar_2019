/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** exec_lldi.c
*/

#include "../include/my.h"

int argu(machine_t *machine, int code[4], \
char *binary, champion_t *champion)
{
    int result = 0;

    if (binary[code[3] + 1] == '0') {
        result = get_good_number(machine, code[2], IND_SIZE);
    } else {
        result = get_good_number(machine, code[2], IND_SIZE);
        result = (champion->pc + result) % MEM_SIZE;
        result = get_good_number(machine, result, IND_SIZE);
    }
    return (result);
}

void write_in(machine_t *machine, int args[3], champion_t *champion)
{
    int sum = args[0] + args[1];
    int address = 0;

    if (args[2] < 0 || args[2] > REG_NUMBER - 1)
        return;
    if (sum == 0)
        champion->carry = 1;
    else
        champion->carry = 0;
    address = \
    (champion->pc + sum) % MEM_SIZE;
    for (int i = 0; i < REG_SIZE; i += 1) {
        champion->registers[args[2]][i] = \
        machine->grid[address].c;
        address += 1;
        if (address >= MEM_SIZE)
            address = 0;
    }
}

void exec_lldi(machine_t *machine, champion_t *champion)
{
    char *binary = find_coding_byte(machine, champion);
    int good_pc = champion->pc + 2;
    int args[3] = {0, 0, 0};
    int code[4] = {0, 0, good_pc, 0};

    if (nb_params(binary) != 3 || binary[0] == '0' || \
    binary[2] == '0' || binary[4] == '1')
        return (update_easy_pc(champion));
    args[0] = argu(machine, code, binary, champion);
    code[2] += 2;
    code[2] = code[2] % MEM_SIZE;
    code[3] += 2;
    args[1] = argu(machine, code, binary, champion);
    code[2] += 2;
    code[2] = code[2] % MEM_SIZE;
    args[2] = get_good_number(machine, code[2], T_REG) - 1;
    write_in(machine, args, champion);
    champion->pc = (champion->pc + 7) % MEM_SIZE;
}