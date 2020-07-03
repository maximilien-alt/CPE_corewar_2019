/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** analyse.c
*/

#include "../include/my.h"

champion_t init_champion(void)
{
    champion_t champion;

    champion.name = NULL;
    champion.nodes = NULL;
    champion.header = my_malloc(sizeof(header_t));
    champion.header->magic = COREWAR_EXEC_MAGIC;
    champion.header->prog_size = 0;
    my_memset(champion.header->prog_name, 0, PROG_NAME_LENGTH + 1);
    my_memset(champion.header->comment, 0, COMMENT_LENGTH + 1);
    return (champion);
}

char *good_string(char *str)
{
    char **tab = my_str_to_word_array(str, "\"");

    return (tab[1]);
}

void complete_header(char *str, champion_t *champion, int name)
{
    static int check_name = 0;
    static int check_comment = 0;

    check_wrong_str(str);
    if (!str || !str[0] || str[my_strlen(str) - 1] != '"')
        exit (84);
    if (name) {
        if (check_name || my_strlen(str) - 3 > PROG_NAME_LENGTH)
            exit (84);
        check_name += 1;
        my_strcpy(champion->header->prog_name, good_string(str));
    } else {
        if (check_comment || my_strlen(str) - 4 > COMMENT_LENGTH || !check_name)
            exit (84);
        check_comment += 1;
        my_strcpy(champion->header->comment, good_string(str));
    }
}

void complete_struct(char **tab, champion_t *champion)
{
    char **temp_tab = NULL;
    int check = 0;

    for (int index = 0; tab[index]; index += 1) {
        temp_tab = my_str_to_word_array(tab[index], " \t,");
        if (!temp_tab || !temp_tab[0] || temp_tab[0][0] == COMMENT_CHAR)
            continue;
        check = 0;
        if (!my_strcmp(temp_tab[0], NAME_CMD_STRING)) {
            complete_header(&tab[index][5], champion, 1);
            check += 1;
        }
        if (!my_strcmp(temp_tab[0], COMMENT_CMD_STRING)) {
            complete_header(&tab[index][8], champion, 0);
            check += 1;
        }
        if (!check)
            complete_nodes(temp_tab, champion, tab[index], 0);
    }
}

int create_champion(char **tab, char *filepath)
{
    char **path = my_str_to_word_array(filepath, "/");
    char **new_file = NULL;
    char *good_name = NULL;
    int index = 0;
    champion_t champion = init_champion();

    for (; path[index + 1]; index += 1);
    new_file = my_str_to_word_array(path[index], ".");
    if (new_file[1] && !new_file[2] && !my_strcmp(new_file[1], "s")) {
        good_name = my_strcat(new_file[0], ".cor");
        champion.name = good_name;
        complete_struct(tab, &champion);
        if (!champion.header->prog_name[0])
            return (84);
        write_in_file(champion);
        return (0);
    }
    return (84);
}