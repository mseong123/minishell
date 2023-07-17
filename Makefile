SRCS_NAME = minishell utils signal tokenisation expand_dollar expand_token expand_utils1 expand_utils2 expand_utils3 expand_utils4 heredoc heredoc_utils parse_error parse_token parse_utils exec_token exec_utils1 exec_utils2 exec_utils3 exec_utils4 exec_utils5 check_builtin check_cd_builtin check_export_builtin check_unset_builtin check_exit_builtin mini_echo mini_cd mini_pwd mini_env mini_export mini_export_utils1 mini_export_utils2 mini_unset mini_unset_utils mini_exit free

SRCS = $(SRCS_NAME:=.c)

OBJECTS = $(SRCS:.c=.o)

NAME = minishell

CFLAGS = -Wall -Wextra -Werror -g3

READLINE_DIR = $(shell brew --prefix readline)

all: $(NAME)

%.o: %.c
	$(CC) -c $(CFLAGS) -I $(READLINE_DIR)/include -I ./libft $<

$(NAME): $(OBJECTS)
	make bonus -C ./libft
	cc $(CFLAGS) $(OBJECTS) -o $(NAME) -lreadline -L$(READLINE_DIR)/lib -L./libft -lft 

clean:
	make clean -C ./libft
	rm -f $(OBJECTS)

fclean: clean
	make fclean -C ./libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
