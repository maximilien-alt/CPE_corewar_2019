/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** champions.c
*/

#include "../include/my.h"

void fill_champ(machine_t *machine, char *filepath, int index)
{
    int check_adress = 0;
    int check_player = 0;

    if (machine->champions[index]->adress == -1)
        machine->champions[index]->adress = index * \
        (MEM_SIZE / machine->nbr_champs);
    if (machine->champions[index]->player == -1)
        machine->champions[index]->player = index + 1;
    for (int i = 0; i < machine->nbr_champs && \
    machine->champions[i]->adress != -1; i += 1) {
        check_adress = machine->champions[i]->adress;
        check_player = machine->champions[i]->player;
        for (int j = 0; j < machine->nbr_champs; j += 1)
            if (j != i && (machine->champions[j]->adress == check_adress || \
            machine->champions[j]->player == check_player))
                exit (84);
        machine->champions[i]->pc = check_adress;
    }
    read_champion(machine, filepath, index);
}

void init_grid(machine_t *machine)
{
    int h = 0;

    for (int index = 0; index < machine->nbr_champs; index += 1) {
        h = 0;
        for (int i = machine->champions[index]->adress; h < \
        machine->champions[index]->header.prog_size; i += 1) {
            if (i >= MEM_SIZE)
                i = 0;
            if (machine->grid[i].color != 0)
                exit (84);
            machine->memory[i] = machine->champions[index]->code[h];
            machine->grid[i].c = machine->champions[index]->code[h];
            machine->grid[i].pos = i;
            machine->grid[i].color = index + 1;
            h += 1;
        }
    }
}

void complete_champions(machine_t *machine, int ac, char **av, int pos[4])
{
    int check[2] = {0, ac};

    if (pos[0] == -1)
        exit (84);
    if (!my_strcmp("-dump", av[1])) {
        if (ac > 2 && my_str_isnum(av[2]))
            machine->nbr_cycles = my_getnbr(av[2]);
        else
            exit (84);
        check[0] += 2;
    }
    for (int index = 0; pos[index] != -1; index += 1) {
        for (check[0] += 1; check[0] < pos[index]; check[0] += 2)
            update_champion(machine, index, av, check);
        fill_champ(machine, av[pos[index]], index);
    }
    init_grid(machine);
}

void create_grid(machine_t *machine)
{
    machine->grid = my_malloc(sizeof(grid_t) * MEM_SIZE);
    machine->memory = my_malloc(sizeof(grid_t) * MEM_SIZE);
    for (int index = 0; index < MEM_SIZE; index += 1) {
        machine->grid[index].c = 0;
        machine->grid[index].color = 0;
        machine->memory[index] = 0;
        machine->grid[index].pos = index;
    }
}

void init_machine(machine_t *machine, int ac, char **av)
{
    int nbr_champs = 0;
    int pos[4] = {-1, -1, -1, -1};

    for (int index = 1; index < ac; index += 1)
        if (is_good_champion(av[index])) {
            if (nbr_champs == 4)
                exit (84);
            pos[nbr_champs] = index;
            nbr_champs += 1;
        }
    machine->nbr_champs = nbr_champs;
    machine->save_index = 0;
    machine->nbr_cycles = 0;
    machine->total_cycle = 0;
    machine->champions = init_champ(nbr_champs);
    create_grid(machine);
    machine->cycle_to_die = CYCLE_TO_DIE;
    machine->cycles_living = 0;
    machine->call_to_live = 0;
    complete_champions(machine, ac, av, pos);
}