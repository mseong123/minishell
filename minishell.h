/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:44:01 by melee             #+#    #+#             */
/*   Updated: 2023/07/17 10:37:47 by melee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define WRITE_END 1
# define READ_END 0
# define READLINE_MSG	"\033[1;34mminishell\033[36m$ \033[0m"
# define WELCOME_MSG "\033[96m╔════════════════════════════════════════════════\
════════════════════════════════╗\n║\
                                                                                ║\n\
║                                                                                ║\n\
║      \033[1;34m ███╗░░░███╗██╗███╗░░██╗██╗░██████╗██╗░░██╗███████╗██╗░░░░░██╗░░░░░\033[96m	 \
║\n║      \033[1;34m ████╗░████║██║████╗░██║██║██╔════╝██║░░██║██╔════╝██║░░░░░██║░░░░░       \033[96m\
║\n║     \033[1;34m  ██╔████╔██║██║██╔██╗██║██║╚█████╗░███████║█████╗░░██║░░░░░██║░░░░░       \033[96m\
║\n║     \033[1;34m  ██║╚██╔╝██║██║██║╚████║██║░╚═══██╗██╔══██║██╔══╝░░██║░░░░░██║░░░░░       \033[96m\
║\n║     \033[1;34m  ██║░╚═╝░██║██║██║░╚███║██║██████╔╝██║░░██║███████╗███████╗███████╗       \033[96m\
║\n║      \033[1;34m ╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═╝╚═════╝░╚═╝░░╚═╝╚══════╝╚══════╝╚══════╝       \033[96m\
║\n║                                                                                ║\n\
╚══════════════════════════════════════════════════════════════════════════\
══════╝"

# include "libft.h"
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <fcntl.h>
# include <sys/stat.h>

typedef struct s_shell
{	
	char	*line;
	int		pid[1392];
	int		pid_count;
	t_list	*token;
	int		heredocfd[500][2];
	int		heredoc_pipe_count;
	int		heredoc_pid;
	int		heredoc_interrupt;
	int		heredoc_exit_status;
	int		pipefd[500][2];
	char	**bin_path;
	char	**builtin_bin_path;
	char	**local_envp;
	int		exit_status;
}	t_shell;

typedef struct s_child
{
	char	*path;
	char	*cmd;
	int		count;
	int		*r_fd;
	int		*w_fd;
	t_list	*token;
}	t_child;

void	set_signal_action(void);
void	set_term(void);
void	sigint_handler1(int signal);
void	sigint_handler2(int signal);
char	**copy_envp(char **envp);
int		count_envp(char **envp);
void	expand_dollar(t_shell *shell);
void	tokenisation(t_shell *shell);
void	free_struc(t_shell *shell, int newline);
void	free_split(char **split);
void	free_child(t_child *child);
void	expand_token(t_shell *shell);
void	expand_operators(t_list *token);
void	ft_printf(void *content);
void	del(void *content);
void	parse_token(t_shell *shell);
int		count_arg(t_list *token);
void	exec_token(t_shell *shell, t_list *token, int count);
void	handle_quote(char c, int *quote);
char	*free_substr_join(char *res, char *substr);
char	*free_join1(char *res, char *str);
char	*parse_nondollar(char *res, char **str);
char	*parse_dollar(t_shell *shell, char *res, char **str);
char	*parse_exit_status(t_shell *shell, char *res, char **str);
char	*ft_getenv(t_shell *shell, char *substr);
int		count_pipes(t_list *token);
void	init_pipefd(t_shell *shell);
void	close_all_pipefd(t_shell *shell);
void	close_all_heredoc_pipe(t_shell *shell);
void	get_cmd(t_shell *shell, t_child *child);
char	*append_slash(char *path, char *input);
int		have_middle_quotes(t_list *token);
void	remove_quotes(t_list *token);
void	parse_error(t_shell *shell);
void	check_w_redirect(t_shell *shell, t_child *child);
void	check_r_redirect(t_shell *shell, t_child *child);
int		have_enclosed_quotes(t_list *token);
void	remove_enclosed_quotes(t_list *token);
void	print_cmd_err(t_shell *shell, t_child *child, char *str);
void	set_pipes(t_shell *shell, t_child *child);
void	parse_heredoc(t_shell *shell);
char	*heredoc_expand_dollar(t_shell *shell, char *line);
void	init_read_fd(t_child *child);
void	init_write_fd(t_child *child);
void	set_redirect_fd(t_shell *shell, t_child *child);
void	exec_cmd(t_shell *shell, t_child *child);
int		check_builtin(t_shell *shell, t_child *child, t_list *token);
void	check_cd_builtin(t_shell *shell, t_child *child, t_list *token);
void	check_export_builtin(t_child *child, t_list *token);
void	check_unset_builtin(t_child *child, t_list *token);
void	check_exit_builtin(t_shell *shell, t_child *child, t_list *token);
void	print_cd_err(t_shell *shell, t_child *child, char *str);
int		skip2(t_list **token, int count);
int		skip1(t_list **token, int count);
void	mini_echo(t_shell *shell, t_child *child);
int		if_redirect(char *str);
void	mini_cd(t_shell *shell, t_child *child);
void	mini_pwd(t_shell *shell, t_child *child);
void	mini_env(t_shell *shell, t_child *child);
void	mini_export(t_shell *shell, t_child *child);
void	mini_exit(t_shell *shell, t_child *child);
int		check_any_export_arg(t_list *token, int count);
char	*get_cd(t_shell *shell);
int		check_cd(t_shell *shell);
void	wait_cd(t_shell *shell);
void	wait_export(t_shell *shell);
void	wait_unset(t_shell *shell);
void	wait_exit(t_shell *shell);
void	insert_env(t_shell *shell, char *str);
void	remove_env(t_shell *shell, char *str);

#endif
