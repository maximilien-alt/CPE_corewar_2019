/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** complete_nodes.c
*/

#include "../include/my.h"

int my_tab_len(char **tab)
{
    int len = 0;

    if (!tab)
        return (0);
    for (; tab[len]; len += 1);
    return (len);
}

int check_for_label(char *str)
{
    int len = my_strlen(str);
    int check = 0;
    int index = 0;

    if (str[len - 1] != LABEL_CHAR)
        return (0);
    for (; str[index]; index += 1)
        for (int temp = 0; LABEL_CHARS[temp]; temp += 1)
            if (LABEL_CHARS[temp] == str[index])
                check += 1;
    if (check != index - 1)
        exit (84);
    return (1);
}

int spe_tab_len(char **tab)
{
    int len = 0;

    for (; tab[len]; len += 1)
        if (tab[len][0] == COMMENT_CHAR)
            break;
    return (len);
}

char *check_instruction(char *str)
{
    for (int index = 0; index < 16; index += 1)
        if (!my_strcmp(str, op_tab[index].mnemonique))
            return (my_strdup(str));
    exit (84);
}

void complete_nodes(char **temp_tab, champion_t *champion, \
char *line, int temp)
{
    args_t args = {NULL, NULL, 0, NULL, false, NULL};
    int tab_len = spe_tab_len(temp_tab);

    args.line = my_strdup(line);
    args.label = check_for_label(temp_tab[0]) ? true : false;
    args.label_str = args.label ? my_strdup(temp_tab[0]): NULL;
    if (args.label_str)
        args.label_str[my_strlen(args.label_str) - 1] = 0;
    if (tab_len <= 1 && args.label)
        return (add_node(&champion->nodes, args));
    if (tab_len <= 1 || tab_len > MAX_ARGS_NUMBER + 2)
        exit (84);
    temp += args.label ? 1 : 0;
    args.instruction = check_instruction(temp_tab[temp]);
    args.args = my_tabdup(&temp_tab[temp + 1]);
    for (temp += 1; temp_tab[temp]; temp += 1) {
        if (temp_tab[temp][0] == COMMENT_CHAR)
            break;
        args.nbr_args += 1;
    }
    add_node(&champion->nodes, args);
}