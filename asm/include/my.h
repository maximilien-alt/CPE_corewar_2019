/*
** EPITECH PROJECT, 2019
** my
** File description:
** include
*/

#ifndef MY_H_
#define MY_H_

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <sys/sysmacros.h>
#include <signal.h>
#include <stdbool.h>
#include "./garbage_collector.h"
#include "./op.h"

typedef struct args_s
{
    char *line;
    char *instruction;
    int nbr_args;
    char **args;
    bool label;
    char *label_str;
} args_t;

typedef struct params_s
{
    int type;
    char *parameter;
    char *binary;
    int bytes_size;
    bool label;
} params_t;

typedef struct nodes_s
{
    bool label;
    bool coding_byte;
    char *label_str;
    char *line;
    char *instruction;
    int nbr_args;
    char **args;
    int *to_write;
    int *bytes_stack;
    params_t *params;
    struct nodes_s *next;
    struct nodes_s *previous;
} nodes_t;

typedef struct champion_s
{
    char *name;
    header_t *header;
    nodes_t *nodes;
} champion_t;

typedef struct  op_s
{
    char *mnemonique;
    char nbr_args;
    args_type_t  type[MAX_ARGS_NUMBER];
    char code;
    int nbr_cycles;
    char *comment;
    void (*ptr)(nodes_t *);
} op_t;


typedef struct format_t
{
    char c;
    void (*ptr)(va_list);
} format_t;

extern  op_t    op_tab[];

void check_wrong_str(char *str);
void wrong_line(nodes_t *nodes);
void check_live(nodes_t *nodes);
void check_ld(nodes_t *nodes);
void check_st(nodes_t *nodes);
void check_add(nodes_t *nodes);
void check_and(nodes_t *nodes);
void check_zjmp(nodes_t *nodes);
void check_ldi(nodes_t *nodes);
void check_sti(nodes_t *nodes);
void check_fork(nodes_t *nodes);
void check_aff(nodes_t *nodes);
params_t *check_params(args_t args);
void create_tabs(nodes_t *nodes, int check, args_t args);
params_t indirect_param(params_t params, char *argument);
params_t register_param(params_t params, char *argument);
params_t direct_param(params_t params, char *argument, args_t args);
int my_tab_len(char **tab);
void complete_nodes(char **temp_tab, champion_t \
*champion, char *line, int temp);
char **my_tabdup(char **tab);
int contain(char *str, char c);
void write_in_file(champion_t champion);
void add_node(nodes_t **nodes, args_t args);
int create_champion(char **tab, char *filepath);
void display_usage(void);
char *read_file(char *filepath);
int error_handling(char **buffer, int state);
void my_memset(char *buffer, char c, int number);
int    my_putnbr_base(int nbr, char const *base);
int    my_compute_power_rec(int nb, int p);
int    my_compute_square_root(int nb);
int    my_find_prime_sup(int nb);
int    my_getnbr(char const *str);
int    my_isneg(int n);
int    my_is_prime(int nb);
int    my_lengh(char const *str);
char    **my_malloc_words(char const *str, char **tab);
void    my_putchar(char c);
void    my_put_nbr(int nb);
int     my_putstr(char const *str);
char    *my_revstr(char *str);
int    my_showmem(char const *str, int size);
int    my_showstr(char const *str);
int    my_show_word_array(char * const *tab);
void    my_sort_int_array(int *tab, int size);
char    *my_strcapitalize(char *str);
char    *my_strcat(char *dest, char *src);
char    my_strcmp(char *s1, char *s2);
char    *my_strcpy(char *dest, char const *src);
char    *my_strcpy2(char *dest, char const *src);
char    *my_strdup(char const *src);
int    my_str_isalpha(char const *str);
int    my_str_islower(char const *str);
int    my_str_isnum(char const *str);
int    my_str_isprintable(char const *str);
int    my_str_isupper(char const *str);
int    my_strlen(char const *str);
char    *my_strlowcase(char *str);
char    *my_strncat(char *dest, char const *src, int nb);
int    my_strncmp(char *s1, char *s2, int n);
char    *my_strncpy(char *dest, char const *src, int n);
char    *my_strstr(char *str, char const *to_find);
char    **my_str_to_word_array(char const *str, char *operator);
char    *my_strupcase(char *str);
void    my_swap(int *a, int *b);
int    my_prime(int nb);
int    my_strlen4(char const *str);
void    my_swap3(char const *dest, char const *src);
void    **my_malloc_word(char const *str, char * const *tab);
int    my_word_number(char const *str);
char   **my_word_in_tab(char const *str, char *const *tab);
int    my_str_neg(char *str, char *str2);
char    *my_infin_add_neg(char *str, char *str2);
int    my_str_is_negative(char *str);
char    *my_str_delete_null(char *str);
char    *my_cpy_without_null(char *str, char *cpy, int letter, int zero);
char    *my_supr_null(char *str, char *cpy, int letter);
char    *my_str_is_easy(char *str, char *cpy);
int    my_int_nbr(char const *str, int letter, int size, char **endptr);
int    my_delete_non_null(char const *str);
int    my_str_tol_error(char const *str);
char    *my_infin_add(char *str, char *str2);
char    *my_infin_add_neg(char *str, char *str2);
int    my_infin_cmp(char *str, char *str2);
char *my_supr_same(char *str, char *strtemp);
char *my_delete_neg(char *str);
char *my_strtemp(char *str, char *div);
int my_mult_zero(char *mult);
char *my_add_x_zero(int cursor);
int    my_clean_add_total(char *str, char *mult);
char *my_delete_mult(char *mult);
char *my_zeroo(char *str, char *mult);
char *my_infin_tol(char *str, char **endptr);
int my_bistro_error(int ac, char **av, char *buff);
char *my_infin_sub(char *str, char *str2);
int my_occ(char *str);
void my_putchar(char c);
void my_print_s(va_list ap);
void my_print_c(va_list ap);
void my_print_d(va_list ap);
void my_print_p(va_list ap);
void my_print_x(va_list ap);
void my_print_upcase_x(va_list ap);
void my_print_o(va_list ap);
void my_print_b(va_list ap);
void my_print_u(va_list ap);
void my_print_upcase_s(va_list ap);
void my_printf(char *format, ...);

#endif /* MY_H_ */
