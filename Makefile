##
## EPITECH PROJECT, 2019
## CPE_corewar_2019
## File description:
## Makefile
##

all	:
		make -C asm
		make -C corewar

clean	:
		make clean -C asm
		make clean -C corewar

fclean	: clean
	make fclean -C asm
	make fclean -C corewar

re	: fclean all