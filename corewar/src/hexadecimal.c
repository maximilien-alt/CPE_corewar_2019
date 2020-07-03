/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** hexadecimal.c
*/

#include "../include/my.h"

int get_good_number(machine_t *machine, int index, int size)
{
    int number = 0;
    int check = machine->grid[index % MEM_SIZE].c;

    for (int j = 0; j < size; j += 1) {
        number = number << 8;
        if (j != 0 && machine->grid[index % MEM_SIZE].c < 0 && \
        check == -1)
            return (machine->grid[index % MEM_SIZE].c);
        number += machine->grid[index % MEM_SIZE].c;
        index += 1;
    }
    return (number < 0 ? (unsigned int)number : (unsigned char)number);
}

char *dec_to_hexa(int dec)
{
    char *hexa = malloc(sizeof(char) * 10);
    int check = 0;

    my_memset(hexa, 0, 10);
    if (dec < 0)
        dec += 256;
    if (dec == 0)
        hexa[0] = '0';
    for (int index = 0; dec != 0; index += 1) {
        check = dec % 16;
        if (check < 10)
            hexa[index] = check + '0';
        else
            hexa[index] = check + '7';
        dec /= 16;
    }
    return (my_revstr(hexa));
}

int hexa_to_dec(char *hexa)
{
    int len = my_strlen(hexa);
    int pow = 1;
    int result = 0;

    if (!hexa)
        return (-1);
    for (int index = len - 1; index >= 0; index -= 1) {
        if (hexa[index] >= '0' && hexa[index] <= '9') {
            result += (hexa[index] - '0') * pow;
        } else {
            if (hexa[index] >= 'A' && hexa[index] <= 'F')
                result += (hexa[index] - 55) * pow;
            if (hexa[index] >= 'a' && hexa[index] <= 'f')
                result += (hexa[index] - 87) * pow;
        }
        pow *= 16;
    }
    return (result);
}