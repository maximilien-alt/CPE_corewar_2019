/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** my_memset.c
*/

void my_memset(char *buffer, char c, int number)
{
    for (int index = 0; index < number; index += 1)
        buffer[index] = c;
}