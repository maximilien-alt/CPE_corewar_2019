/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** parsing.c
*/

#include "../include/my.h"

char **my_tabdup(char **tab)
{
    int len = 0;
    int index = 0;
    char **new_tab = NULL;

    if (!tab)
        return (NULL);
    for (; tab[len]; len += 1);
    new_tab = my_malloc(sizeof(char *) * (len + 1));
    for (; tab[index]; index += 1)
        new_tab[index] = my_strdup(tab[index]);
    new_tab[index] = NULL;
    return (new_tab);
}

params_t good_struct(args_t args, int index)
{
    params_t params;
    char *argument = my_strdup(args.args[index]);

    params.parameter = argument;
    if (argument[0] == 'r')
        return (register_param(params, argument));
    if (argument[0] == DIRECT_CHAR)
        return (direct_param(params, argument, args));
    return (indirect_param(params, argument));
}

params_t *check_params(args_t args)
{
    int len = my_tab_len(args.args);
    params_t *params = my_malloc(sizeof(params_t) * len);

    if (!args.args)
        return (NULL);
    for (int index = 0; args.args[index]; index += 1) {
        if (args.args[index][0] == COMMENT_CHAR) {
            args.args[index] = NULL;
            params[index].type = -1;
            break;
        }
        params[index] = good_struct(args, index);
    }
    return (params);
}

nodes_t *create_node(args_t args)
{
    nodes_t *new_node = my_malloc(sizeof(nodes_t));

    if (args.nbr_args > 4)
        exit (84);
    new_node->coding_byte = true;
    new_node->line = my_strdup(args.line);
    new_node->instruction = my_strdup(args.instruction);
    new_node->nbr_args = args.nbr_args;
    new_node->args = my_tabdup(args.args);
    new_node->to_write = NULL;
    new_node->bytes_stack = NULL;
    new_node->label = args.label;
    new_node->label_str = my_strdup(args.label_str);
    create_tabs(new_node, 0, args);
    new_node->next = NULL;
    new_node->previous = NULL;
    return (new_node);
}

void add_node(nodes_t **nodes, args_t args)
{
    nodes_t *new_node = create_node(args);
    nodes_t *copy_node = *nodes;

    if (!copy_node)
        *nodes = new_node;
    else {
        while (copy_node->next)
            copy_node = copy_node->next;
        copy_node->next = new_node;
        new_node->previous = copy_node;
    }
}