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
#include "./op.h"
#include "./garbage_collector.h"

typedef struct champion_s
{
    header_t header;
    int player;
    int adress;
    int carry;
    char *code;
    int pc;
    char **registers;
    bool alive;
    int cycles_waiting;
    int cycle_to_live;
    bool waiting;
    int color;
    struct champion_s *next;
} champion_t;

typedef struct grid_s
{
    char c;
    int color;
    int pos;
} grid_t;

typedef struct coding_s
{
    int index;
    int pc;
} coding_t;

typedef struct machine_s
{
    int nbr_champs;
    int nbr_cycles;
    champion_t **champions;
    char *memory;
    grid_t *grid;
    int cycle_to_die;
    int call_to_live;
    int save_index;
    int cycles_living;
    int total_cycle;
} machine_t;

typedef struct  op_s
{
    char *mnemonique;
    int nbr_args;
    args_type_t  type[MAX_ARGS_NUMBER];
    int code;
    int nbr_cycles;
    char *comment;
    void (*ptr)(machine_t *, champion_t *);
} op_t;

extern  op_t    op_tab[];

typedef struct format_t
{
    char c;
    void (*ptr)(va_list);
} format_t;

void good_winning_print(machine_t *);
void update_easy_pc(champion_t *champion);
int get_good_pc(char *binary, int good_pc);
void exec_direct(machine_t *machine, champion_t *champion, \
int good_pc, int reg);
int find_argument(machine_t *machine, champion_t *champion, \
char *binary, coding_t coding);
void add_champion(champion_t **champion, int new_pc);
int did_someone_win(machine_t *machine);
bool *new_bools(machine_t *machine, int len, int index);
void check_for_loose(machine_t *machine);
int *new_cycles(machine_t *machine, int len, int index);
int *new_tab(machine_t *machine, int len, int index);
int calc_register(char *reg);
int get_good_number(machine_t *machine, int index, int size);
void wrong_parameters(machine_t *machine, champion_t *champion, \
char *binary, bool excep);
int nb_params(char *binary);
char *find_coding_byte(machine_t *machine, champion_t *champion);
void exec_live(machine_t *machine, champion_t *);
void exec_ld(machine_t *machine, champion_t *);
void exec_st(machine_t *machine, champion_t *);
void exec_add(machine_t *machine, champion_t *);
void exec_sub(machine_t *machine, champion_t *);
void exec_and(machine_t *machine, champion_t *);
void exec_or(machine_t *machine, champion_t *);
void exec_xor(machine_t *machine, champion_t *);
void exec_zjump(machine_t *machine, champion_t *);
void exec_ldi(machine_t *machine, champion_t *);
void exec_sti(machine_t *machine, champion_t *);
void exec_fork(machine_t *machine, champion_t *);
void exec_lld(machine_t *machine, champion_t *);
void exec_lldi(machine_t *machine, champion_t *);
void exec_lfork(machine_t *machine, champion_t *);
void exec_aff(machine_t *machine, champion_t *);
void print_structure(machine_t *machine);
void loop_game(machine_t *machine);
void update_champion(machine_t *machine, int index, char **av, int check[2]);
champion_t **init_champ(int nbr_champs);
int is_good_champion(char *str);
void complete_champion(machine_t *machine, char *filepath, int index);
void read_champion(machine_t *machine, char *filepath, int index);
void init_machine(machine_t *machine, int ac, char **av);
int hexa_to_dec(char *hexa);
char *dec_to_hexa(int dec);
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
