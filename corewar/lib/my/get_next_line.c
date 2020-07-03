/*
** EPITECH PROJECT, 2019
** B-CPE_2019
** File description:
** get_next_line_v2.c
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char *new_save(char *save, int i)
{
    char *new_save = NULL;
    int check = 0;
    int a = 0;

    for (i = 0; save[i] && save[i] != '\n'; i += 1);
    if (save[i] == '\0') {
        free (save);
        return (NULL);
    }
    for (a = i; save[a]; a += 1);
    new_save = malloc(sizeof(char) * a + 1);
    if (!new_save)
        return (NULL);
    for (int b = i + 1; save[b]; b += 1, check += 1)
        new_save[check] = save[b];
    new_save[check] = '\0';
    return (new_save);
}

char *my_save_char(char *temp, char *save_ori, int a, int check)
{
    char *save = NULL;
    int after = 0;
    int cursor = 0;

    if (!save_ori || !new_save(save_ori, 0)) {
        if (!temp || temp[0] == '\0')
            return (NULL);
        for (cursor = 0; temp[cursor] && temp[cursor] != '\n'; cursor += 1);
        check = cursor + 1;
        cursor += 1;
        for (after = 0; temp[cursor]; after += 1, cursor += 1);
        save = malloc(sizeof(char) * after + 1);
        if (!save)
            return (NULL);
        for (a = 0; temp[check]; check += 1, a += 1)
            save[a] = temp[check];
        save[a] = '\0';
    } else
        save = new_save(save_ori, 0);
    free(temp);
    return (save);
}

int my_special_strlen(char *str, int check)
{
    int len = 0;

    if (!str)
        return (0);
    for (len = 0; str[len]; len += 1) {
        if (str[len] == '\n' && check == 2)
            return (1);
        if (str[len] == '\n' && check == 1)
            return (len);
    }
    if (check == 1)
        return (len);
    return (0);
}

char *my_special_strcat(char *src, char *dest)
{
    char *str_cat = NULL;
    int cat = 0;

    if (!src || src[0] == '\0') {
        str_cat = malloc(sizeof(char) * (my_special_strlen(dest, 1) + 1));
        if (!str_cat)
            return (NULL);
    } else {
        str_cat = malloc(sizeof(char) * my_special_strlen(dest, 1) + \
        my_special_strlen(src, 1) + 1);
        if (!str_cat)
            return (NULL);
    }
    for (cat = 0; src && src[cat]; cat += 1)
        str_cat[cat] = src[cat];
    for (int key = 0; dest[key] && dest[key] != '\n'; key += 1, cat += 1)
        str_cat[cat] = dest[key];
    str_cat[cat] = '\0';
    if (src)
        free (src);
    return (str_cat);
}

char *get_next_line(int fd)
{
    int check = 0;
    char *lign = NULL;
    char *temp = malloc(sizeof(char) * 3 + 1);
    static char *save = NULL;

    if (fd <= 0 || !temp || 3 <= 0)
        return (NULL);
    (save) ? lign = my_special_strcat(lign, save) : 0;
    if (my_special_strlen(save, 2) == 0) {
        check = read(fd, temp, 3);
        temp[check] = '\0';
        while (check > 0 && my_special_strlen(temp, 2) == 0) {
            lign = my_special_strcat(lign, temp);
            check = read(fd, temp, 3);
            temp[check] = '\0';
        }
    }
    (check != 0) ? lign = my_special_strcat(lign, temp) : 0;
    save = my_save_char(temp, save, 0, 0);
    return ((!lign && !save && check == 0) || \
    (lign && lign[0] == '\0' && !save)) ? NULL : lign;
}