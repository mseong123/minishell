/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:47:01 by melee             #+#    #+#             */
/*   Updated: 2023/06/28 15:00:07 by melee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_waitpid(t_shell *shell)
{
	int	pid_count;
	int	i;

	pid_count = shell->pid_count;
	i = 0;
	while (i < pid_count)
	{
		waitpid(shell->pid[i], &shell->exit_status, 0);
		if (WIFSIGNALED(shell->exit_status) && i == 0 \
			&& WTERMSIG(shell->exit_status) == SIGQUIT)
			write(1, "^\\Quit: 3\n", 10);
		if (WIFSIGNALED(shell->exit_status) && i == 0 && \
			WTERMSIG(shell->exit_status) == SIGINT)
			write(1, "^C\n", 3);
		wait_cd(shell);
		wait_export(shell);
		wait_unset(shell);
		wait_exit(shell);
		i++;
	}
}

char	**get_bin_path(char **local_envp)
{
	char	*res_str;
	int		i;

	i = 0;
	while (local_envp[i])
	{
		if (!ft_strncmp(local_envp[i], "PATH=", ft_strlen("PATH=")))
		{
			res_str = ft_strchr(local_envp[i], '=');
			res_str++;
			return (ft_split(res_str, ':'));
		}
		i++;
	}
	return (NULL);
}

void	init(t_shell *shell)
{
	shell->heredoc_interrupt = 0;
	shell->line = NULL;
	shell->pid_count = 0;
	shell->token = NULL;
	shell->heredoc_pipe_count = 0;
	shell->bin_path = get_bin_path(shell->local_envp);
}

void	readloop(t_shell *shell)
{
	set_signal_action();
	init(shell);
	shell->line = readline(READLINE_MSG);
	if (shell->line == NULL)
	{
		free_struc(shell, 0);
		exit(EXIT_SUCCESS);
	}
	add_history(shell->line);
	expand_dollar(shell);
	tokenisation(shell);
	expand_token(shell);
	parse_error(shell);
	parse_heredoc(shell);
	if (shell->heredoc_interrupt == 0)
	{
		parse_token(shell);
		set_waitpid(shell);
	}
	free_struc(shell, 1);
	readloop(shell);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argv;
	if (argc == 1)
	{
		printf("\n%s\n\n", WELCOME_MSG);
		shell.local_envp = copy_envp(envp);
		set_term();
		shell.builtin_bin_path = get_bin_path(shell.local_envp);
		readloop(&shell);
	}
	return (EXIT_SUCCESS);
}
