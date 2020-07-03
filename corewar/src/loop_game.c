/*
** EPITECH PROJECT, 2019
** corewar
** File description:
** loop_game.c
*/

#include "../include/my.h"

void catch_instruction_next(machine_t *machine, \
int instruction, champion_t *champion)
{
    if (champion->waiting) {
        champion->cycles_waiting -= 1;
        if (champion->cycles_waiting)
            return;
    }
    champion->waiting = false;
    for (int index = 0; index < 16; index += 1) {
        if (instruction == op_tab[index].code) {
            op_tab[index].ptr(machine, champion);
            return;
        }
    }
}

void catch_instruction(machine_t *machine, \
int instruction, champion_t *champion)
{
    if (!champion->waiting) {
        for (int index = 0; index < 16; index += 1)
            if (instruction == op_tab[index].code) {
                champion->waiting = true;
                champion->cycles_waiting = \
                op_tab[index].nbr_cycles - 1;
                return;
            }
        champion->pc += 1;
        if (champion->pc >= MEM_SIZE)
            champion->pc = 0;
        return;
    }
    catch_instruction_next(machine, instruction, champion);
}

void parse_champions(machine_t *machine, int good_pc, int instruction)
{
    for (int index = 0; index < machine->nbr_champs; index += 1) {
        if (!machine->champions[index]->alive)
            continue;
        for (champion_t *champion = machine->champions[index]->next; \
        champion; champion = champion->next) {
            good_pc = champion->pc;
            instruction = get_good_number(machine, good_pc, 1);
            catch_instruction(machine, instruction, champion);
        }
        good_pc = machine->champions[index]->pc;
        instruction = get_good_number(machine, good_pc, 1);
        catch_instruction(machine, instruction, machine->champions[index]);
    }
}

int get_new_cycle(machine_t *machine, int cycle, char *hexa)
{
    if (cycle)
        return (cycle);
    for (int index = 0; index < MEM_SIZE; index += 1) {
        hexa = dec_to_hexa(machine->grid[index].c);
        if (my_strlen(hexa) == 1)
            hexa = my_strcat("0", hexa);
        if (machine->grid[index].color == 1)
            my_printf("%s", "\033[0;31m");
        if (machine->grid[index].color == 2)
            my_printf("%s", "\033[0;32m");
        if (machine->grid[index].color == 3)
            my_printf("%s", "\033[0;33m");
        if (machine->grid[index].color == 4)
            my_printf("%s", "\033[0;34m");
        if (index % 32 == 0) {
            (index == 0) ? my_printf("%s", hexa) : my_printf("\n%s", hexa);
        } else
            my_printf(" %s", hexa);
        my_printf("%s", "\033[0m");
    }
    good_winning_print(machine);
}

void print_structure(machine_t *machine)
{
    for (int index = 0; index < machine->nbr_champs; index += 1) {
        printf("Champion %s, Numero %d\n", machine->champions[index]->header.prog_name, machine->champions[index]->player);
        printf("REGISTERS :\n");
        for (champion_t *champion = machine->champions[index]; champion; champion = champion->next) {
            for (int i = 0; i < 16; i += 1) {
                for (int u = 0; u < REG_SIZE; u += 1)
                    printf("%02hhx", machine->champions[index]->registers[i][u]);
                printf("|");
            }
            printf(" Waiting cycle : %d\n", champion->cycles_waiting);
        }
        printf("Calls to live : %d, Carry : %d\n", machine->champions[index]->cycle_to_live, machine->champions[index]->carry);
    }
    printf("Total calls to live : %d/%d, cycle to die : %d/%d\n", machine->call_to_live, NBR_LIVE, machine->cycles_living, machine->cycle_to_die);
    //for (int index = 0; index < MEM_SIZE; index += 1) {
    //    if (machine->grid[index].color == 1)
    //        printf("\033[0;31m");
    //    if (machine->grid[index].color == 2)
    //        printf("\033[0;32m");
    //    if (machine->grid[index].color == 3)
    //        printf("\033[0;33m");
    //    if (machine->grid[index].color == 4)
    //        printf("\033[0;34m");
    //    for (int h = 0; h < machine->nbr_champs; h += 1) {
    //        for (champion_t *mac = machine->champions[h]; mac; mac = mac->next)
    //            if (index == mac->pc)
    //                printf("\033[5m");
    //    }
    //    if (index != 0 && index % 96 == 0)
    //        printf("\n");
    //    printf("%02hhx ", machine->grid[index].c);
    //    printf("\033[0m");
    //}
    //printf("\n");
}

void loop_game(machine_t *machine)
{
    int cycle = machine->nbr_cycles;

    do {
        //printf("\e[1;1H\e[2J");
        //print_structure(machine);
        machine->cycles_living += 1;
        machine->total_cycle += 1;
        if (machine->cycles_living >= machine->cycle_to_die)
            check_for_loose(machine);
        if (machine->nbr_cycles != 0) {
            cycle -= 1;
            cycle = get_new_cycle(machine, cycle, NULL);
        }
        parse_champions(machine, 0, 0);
        if (machine->call_to_live >= NBR_LIVE) {
            machine->call_to_live = 0;
            machine->cycle_to_die -= CYCLE_DELTA;
        }
        //getchar();
    } while (!did_someone_win(machine));
}