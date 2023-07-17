/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 10:55:58 by melee             #+#    #+#             */
/*   Updated: 2023/07/06 10:56:37 by melee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_heredoc_pipe(t_list *token)
{
	int	heredoc_pipe;

	heredoc_pipe = 0;
	while (token)
	{
		if (!ft_strcmp(token->content, "<<"))
			heredoc_pipe++;
		token = token->next;
	}
	return (heredoc_pipe);
}

void	init_heredoc_pipe(t_shell *shell)
{
	t_list	*token;
	int		heredoc_pipe;
	int		i;

	token = shell->token;
	heredoc_pipe = count_heredoc_pipe(token);
	i = 0;
	while (i < heredoc_pipe)
	{
		if (pipe(shell->heredocfd[i]) == -1)
		{
			perror("minishell");
			free_struc(shell, 0);
			exit(EXIT_SUCCESS);
		}
		i++;
	}
}

void	here_doc(t_shell *shell, t_list *token, int i)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (!ft_strcmp(line, token->next->content))
		{
			free(line);
			break ;
		}
		line = heredoc_expand_dollar(shell, line);
		write(shell->heredocfd[i][WRITE_END], line, ft_strlen(line));
		write(shell->heredocfd[i][WRITE_END], "\n", 1);
		free(line);
	}
	close_all_heredoc_pipe(shell);
}

void	execute_heredoc(t_shell *shell)
{
	t_list	*token;
	int		i;

	token = shell->token;
	i = 0;
	signal(SIGINT, SIG_DFL);
	while (token)
	{
		if (!ft_strcmp(token->content, "<<"))
		{
			here_doc(shell, token, i);
			token = token->next->next;
			i++;
		}
		else
			token = token->next;
	}
	free_struc(shell, 0);
	exit(EXIT_SUCCESS);
}

void	parse_heredoc(t_shell *shell)
{
	t_list	*token;
	int		i;

	token = shell->token;
	i = 0;
	init_heredoc_pipe(shell);
	signal(SIGINT, sigint_handler1);
	shell->heredoc_pid = fork();
	if (shell->heredoc_pid == -1)
	{
		perror("minishell");
		free_struc(shell, 0);
		exit(EXIT_SUCCESS);
	}
	if (shell->heredoc_pid == 0)
		execute_heredoc(shell);
	waitpid(shell->heredoc_pid, &shell->heredoc_exit_status, 0);
	if (WIFSIGNALED(shell->heredoc_exit_status)
		&& WTERMSIG(shell->heredoc_exit_status) == SIGINT)
	{
		printf("\n");
		shell->heredoc_interrupt = 1;
	}
}
