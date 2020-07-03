/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** params.c
*/

#include "../include/my.h"

int nb_params(char *binary)
{
    int nb_params = 0;

    for (int i = 0; i < 8; i += 2) {
        if (binary[i] == '1' && binary[i + 1] == '1')
            nb_params += 1;
        if (binary[i] == '1' && binary[i + 1] == '0')
            nb_params += 1;
        if (binary[i] == '0' && binary[i + 1] == '1')
            nb_params += 1;
    }
    return (nb_params);
}

void wrong_parameters(machine_t *machine, champion_t *champion, \
char *binary, bool excep)
{
    int nb_bytes = 2;

    (void)machine;
    for (int i = 0; i < 8; i += 2) {
        if (binary[i] == '1' && binary[i + 1] == '1')
            nb_bytes += 2;
        if (binary[i] == '1' && binary[i + 1] == '0')
            nb_bytes += excep ? 2 : 4;
        if (binary[i] == '0' && binary[i + 1] == '1')
            nb_bytes += 1;
    }
    champion->pc += nb_bytes;
    champion->pc = champion->pc % MEM_SIZE;
}