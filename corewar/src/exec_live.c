/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** exec_live.c
*/

#include "../include/my.h"

void check_for_loose(machine_t *machine)
{
    for (int index = 0; index < machine->nbr_champs; index += 1) {
        if (!machine->champions[index]->cycle_to_live)
            machine->champions[index]->alive = false;
        machine->champions[index]->cycle_to_live = 0;
    }
    machine->cycles_living = 0;
}

void exec_live(machine_t *machine, champion_t *champion)
{
    int good_pc = champion->pc;
    int number = get_good_number(machine, good_pc + 1, DIR_SIZE);

    champion->pc = (champion->pc + DIR_SIZE + 1) % MEM_SIZE;
    machine->call_to_live += 1;
    for (int i = 0; i < machine->nbr_champs; i += 1)
        if (machine->champions[i]->player == number) {
            my_printf("The player %d(%s)is alive.\n", \
            machine->champions[i]->player, \
            machine->champions[i]->header.prog_name);
            machine->champions[i]->cycle_to_live += 1;
            machine->save_index = champion->player;
        }
}