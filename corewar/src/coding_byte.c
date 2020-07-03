/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** coding_byte.c
*/

#include "../include/my.h"

char *dec_to_binary(char *binary, int dec)
{
    for (int index = 0; dec > 0; index += 1) {
        if (index == 8)
            return (NULL);
        binary[index] = dec % 2 + '0';
        dec /= 2;
    }
    return (my_revstr(binary));
}

char *find_coding_byte(machine_t *machine, champion_t *champion)
{
    int save_pc = champion->pc + 1;
    char *hexa = NULL;
    int dec = 0;
    char *binary = my_malloc(sizeof(char) * 9);

    for (int i = 0; i < 9; i += 1)
        binary[i] = (i == 8) ? 0 : '0';
    if (save_pc >= MEM_SIZE)
        save_pc = 0;
    hexa = dec_to_hexa((int)machine->grid[save_pc].c);
    dec = hexa_to_dec(hexa);
    binary = dec_to_binary(binary, dec);
    if (!binary)
        return (NULL);
    return (binary);
}