CC			= cc
CFLAGS		= -Wall -Werror -Wextra
RM 			= rm -rf

NAME 		= pipex
HEADER 		= pipex.h

SRC			= pipex.c pipex_utils.c pipex_preprocessing.c 	pipex_errors.c \
			pipex_execute.c pipex_pipes.c
OBJ			= $(SRC:%.c=%.o)

BONUS		= pipex
BONUS_H		= pipex_bonus.h
BONUS_SRC	= pipex_bonus.c pipex_utils.c pipex_bonus_preprocessing.c		pipex_bonus_errors.c \
			pipex_execute.c pipex_pipes.c
BONUS_OBJ = $(BONUS_SRC:.c=.o)

LIBFT		=	libft/libft.a
FT_PRINTF	=	ft_printf/libftprintf.a

all:		libft ft_printf $(NAME)

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(FT_PRINTF) -o $(NAME)

%.o:		%.c $(HEADER) $(BONUS_H)
			$(CC) $(CFLAGS)  -c $< -o $@

libft:
			@$(MAKE) -C libft/

ft_printf:
			@$(MAKE) -C ft_printf/

bonus:		libft ft_printf $(BONUS_OBJ)
			$(CC) $(CFLAGS) $(BONUS_OBJ) $(LIBFT) $(FT_PRINTF) -o $(BONUS)

clean:
			@$(RM) $(OBJ) $(BONUS_OBJ)
			@$(MAKE) -C libft/ clean
			@$(MAKE) -C ft_printf/ clean

fclean:		clean
			@$(MAKE) -C libft/ fclean
			@$(MAKE) -C ft_printf/ fclean
			@$(RM) $(NAME) $(BONUS)

re:			fclean all

.PHONY:		all	clean fclean re libft ft_printf bonus
