/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** write_in_file.c
*/

#include "../include/my.h"

void good_write(nodes_t *copy, int fd)
{
    int tot_len = 0;

    for (int index = 0; copy->to_write[index] != -1; index += 1) {
        tot_len = copy->to_write[index];
        if (copy->bytes_stack[index] != 1) {
            tot_len = SWAP(tot_len);
            if (copy->bytes_stack[index] == IND_SIZE)
                tot_len = (tot_len << 16) | (tot_len >> 16);
        }
        write(fd, &tot_len, copy->bytes_stack[index]);
    }
}

int find_label(nodes_t *nodes, char *comp, int result)
{
    for (nodes_t *copy = nodes; copy; copy = copy->next) {
        if (copy->label && !my_strcmp(comp, copy->label_str))
            return (result);
        if (!copy->args)
            continue;
        for (int index = 0; copy->to_write[index] != -1; index += 1)
            result += copy->bytes_stack[index];
    }
    result = 0;
    for (nodes_t *copy = nodes->previous; copy; copy = copy->previous) {
        if (!copy->args) {
            if (copy->label && !my_strcmp(comp, copy->label_str))
                return (-result);
            continue;
        }
        for (int index = 0; copy->to_write[index] != -1; index += 1)
            result += copy->bytes_stack[index];
        if (copy->label && !my_strcmp(comp, copy->label_str))
            return (-result);
    }
    return (-result);
}

void check_label_exist(champion_t *champion, char *comp)
{
    for (nodes_t *copy = champion->nodes; copy; copy = copy->next) {
        if (copy->label)
            if (!my_strcmp(comp, copy->label_str))
                return;
    }
    exit (84);
}

void good_label(nodes_t *nodes, champion_t *champion)
{
    int cursor = 0;
    char *comp = NULL;

    for (int index = 0; nodes->args && nodes->args[index]; index += 1) {
        if (nodes->params[index].type == -1)
            break;
        if (nodes->params[index].label) {
            cursor = (nodes->coding_byte) ? index + 2 : index + 1;
            comp = (nodes->params[index].type == 2) ? \
            my_strdup(&nodes->args[index][2]) : \
            my_strdup(&nodes->args[index][1]);
            check_label_exist(champion, comp);
            nodes->to_write[cursor] = find_label(nodes, comp, 0);
        }
    }
}

void write_in_file(champion_t champion)
{
    int fd = 0;
    int tot_len = 0;

    for (nodes_t *copy = champion.nodes; copy; copy = copy->next) {
        for (int index = 0; copy->bytes_stack && \
        copy->bytes_stack[index] != -1; index += 1)
            tot_len += copy->bytes_stack[index];
        good_label(copy, &champion);
        wrong_line(copy);
    }
    fd = open(champion.name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (!fd)
        exit (84);
    champion.header->prog_size = SWAP(tot_len);
    champion.header->magic = SWAP(champion.header->magic);
    write(fd, champion.header, sizeof(header_t));
    for (nodes_t *copy = champion.nodes; copy; copy = copy->next) {
        if (!copy->args)
            continue;
        good_write(copy, fd);
    }
}