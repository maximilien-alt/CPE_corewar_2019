/*
** EPITECH PROJECT, 2019
** my_strcpy
** File description:
** my_strcpy
*/

#include <stdlib.h>

char    *my_strcpy(char *dest, char const *src)
{
    int i = 0;

    if (!src || !src[0])
        return ("NULL");
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}
