/*
** EPITECH PROJECT, 2020
** garbage_collector.c
** File description:
** functions for garbage_collector
*/

#include "../include/garbage_collector.h"

garbage_collector_t **get_garbage(void)
{
    static garbage_collector_t *garbage = NULL;

    return (&garbage);
}

void *my_malloc(ssize_t size)
{
    void *ptr = malloc(size);

    add_ptr_to_garbage_collector_t(get_garbage(), ptr);
    return (ptr);
}

void add_ptr_to_garbage_collector_t \
(garbage_collector_t **garbage_collector, void *ptr)
{
    garbage_collector_t *copy = malloc(sizeof(garbage_collector_t));

    copy->ptr = ptr;
    copy->next = *garbage_collector;
    *garbage_collector = copy;
}

void destroy_ptr_to_garbage_collector_t(void)
{
    garbage_collector_t *copy = NULL;
    garbage_collector_t *garbage = *get_garbage();

    while (garbage) {
        copy = garbage;
        garbage = garbage->next;
        free (copy->ptr);
        free (copy);
    }
}
