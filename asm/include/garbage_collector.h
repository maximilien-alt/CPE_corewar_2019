/*
** EPITECH PROJECT, 2020
** garbage_collector.h
** File description:
** for garbage_collector function
*/

#ifndef GARBAGE_COLLECTOR_H_
#define GARBAGE_COLLECTOR_H_

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

typedef struct garbage_collector_s
{
    void *ptr;
    struct garbage_collector_s *next;
} garbage_collector_t;

void *my_malloc(ssize_t size);
void add_ptr_to_garbage_collector_t \
(garbage_collector_t **garbage_collector, void *ptr);
void destroy_ptr_to_garbage_collector_t(void)\
                                        __attribute__ ((destructor));

#endif
