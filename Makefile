NAME = minishell

CC = clang
CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

SRC = tokenization.c\
      utilities.c\
      ft_printout.c\
      ft_identify_token_type.c\
	  ft_identify_redirections.c\
	  ft_free_stuff.c\
	  ft_create_lists.c\
	  ft_create_ast.c\
	  ft_checker_is.c\

OBJ = $(SRC:.c=.o)


LIBFT = libft/libft.a

.PHONY: all bonus clean fclean re

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C libft

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) -lreadline -Llibft -lft -o $(NAME)

%.o: %.c $(LIBFT)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ) $(BONUS_OBJ)
	@make clean -C libft

fclean: clean
	@$(RM) $(NAME) $(BONUS_NAME)
	@make fclean -C libft

re: fclean all