/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** main.c
*/

#include "../include/my.h"

void good_winning_print(machine_t *machine)
{
    for (int index = 0; index < machine->nbr_champs; index += 1) {
        if (machine->champions[index]->player == machine->save_index)
            my_printf("\nThe player %d(%s) has won.\n", \
            machine->champions[index]->player, \
            machine->champions[index]->header.prog_name);
    }
    exit (0);
}

int did_someone_win(machine_t *machine)
{
    int nb_alives = 0;
    int save_index = 0;

    for (int index = 0; index < machine->nbr_champs; index += 1) {
        if (machine->champions[index]->alive) {
            save_index = index;
            nb_alives += 1;
        }
    }
    if (nb_alives == 1) {
        my_printf("The player %d(%s)has won.\n", \
        machine->champions[save_index]->player, \
        machine->champions[save_index]->header.prog_name);
        return (1);
    }
    if (!nb_alives)
        good_winning_print(machine);
    return (0);
}

champion_t *init_new_champ(champion_t *champion, int new_pc)
{
    champion_t *new = my_malloc(sizeof(champion_t));

    new->alive = true;
    new->carry = champion->carry;
    new->code = my_strdup(champion->code);
    new->player = champion->player;
    new->header = champion->header;
    new->adress = champion->adress;
    new->pc = new_pc;
    new->cycles_waiting = 0;
    new->waiting = false;
    new->cycle_to_live = 0;
    new->registers = my_malloc(sizeof(char *) * 16);
    new->color = champion->color;
    for (int i = 0; i < 16; i += 1) {
        new->registers[i] = my_malloc(sizeof(char) * REG_SIZE);
        for (int j = 0; j < REG_SIZE; j += 1)
            new->registers[i][j] = champion->registers[i][j];
    }
    new->next = NULL;
    return (new);
}

void add_champion(champion_t **champion, int new_pc)
{
    champion_t *new_champion = init_new_champ(*champion, new_pc);
    champion_t *copy = *champion;

    if (!champion)
        *champion = new_champion;
    else {
        while (copy->next)
            copy = copy->next;
        copy->next = new_champion;
    }
}

int main(int ac, char **av)
{
    machine_t machine;

    if (ac == 1)
        return (84);
    init_machine(&machine, ac, av);
    if (machine.nbr_champs == 1 || machine.nbr_cycles < 0)
        exit (84);
    loop_game(&machine);
    return (0);
}