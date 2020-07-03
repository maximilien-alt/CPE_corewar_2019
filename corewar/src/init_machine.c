/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** init_mahcine.c
*/

#include "../include/my.h"

int is_good_champion(char *str)
{
    FILE *fd = fopen(str, "r");
    int len = my_strlen(str);

    if (!fd || len <= 4)
        return (0);
    fclose(fd);
    if (!my_strcmp(&str[len - 4], ".cor"))
        return (1);
    return (0);
}

char **create_registers(void)
{
    char **tab = my_malloc(sizeof(char *) * 16);

    for (int index = 0; index < 16; index += 1) {
        tab[index] = my_malloc(sizeof(char) * REG_SIZE);
        my_memset(tab[index], 0, REG_SIZE);
    }
    return (tab);
}

champion_t **init_champ(int nbr_champs)
{
    champion_t **champions = my_malloc(sizeof(champion_t *) * nbr_champs);

    for (int index = 0; index < nbr_champs; index += 1) {
        champions[index] = my_malloc(sizeof(champion_t));
        champions[index]->player = -1;
        champions[index]->adress = -1;
        champions[index]->code = NULL;
        champions[index]->pc = 0;
        champions[index]->cycles_waiting = 0;
        champions[index]->carry = 0;
        champions[index]->registers = create_registers();
        champions[index]->cycle_to_live = 0;
        champions[index]->alive = true;
        champions[index]->waiting = false;
        champions[index]->color = index + 1;
        champions[index]->next = NULL;
    }
    return (champions);
}

void update_champion(machine_t *machine, int index, char **av, int check[2])
{
    if (!my_strcmp("-a", av[check[0]])) {
        if (machine->champions[index]->adress == -1 && check[0] != check[1] && \
        my_str_isnum(av[check[0] + 1])) {
            machine->champions[index]->adress = \
            my_getnbr(av[check[0] + 1]) % MEM_SIZE;
            return;
        } else
            exit (84);
    }
    if (!my_strcmp("-n", av[check[0]])) {
        if (machine->champions[index]->player == -1 && check[0] != check[1] && \
        my_str_isnum(av[check[0] + 1])) {
            machine->champions[index]->player = my_getnbr(av[check[0] + 1]);
            return;
        } else
            exit (84);
    }
    exit (84);
}

void read_champion(machine_t *machine, char *filepath, int index)
{
    int fd = open(filepath, O_RDONLY);

    if (!read(fd, &machine->champions[index]->header, sizeof(header_t)))
        exit (84);
    machine->champions[index]->registers[0][3] = \
    machine->champions[index]->player;
    machine->champions[index]->header.prog_size = \
    SWAP(machine->champions[index]->header.prog_size);
    machine->champions[index]->code = my_malloc(sizeof(char) * \
    machine->champions[index]->header.prog_size + 1);
    my_memset(machine->champions[index]->code, 0, \
    machine->champions[index]->header.prog_size + 1);
    read(fd, machine->champions[index]->code, \
    machine->champions[index]->header.prog_size);
    machine->champions[index]->header.magic = \
    SWAP(machine->champions[index]->header.magic);
    if (machine->champions[index]->header.magic != COREWAR_EXEC_MAGIC)
        exit (84);
    close(fd);
    if (machine->champions[index]->header.prog_size > MEM_SIZE)
        exit (84);
}