/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:11:47 by melee             #+#    #+#             */
/*   Updated: 2023/07/03 17:12:04 by melee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipes(t_list *token)
{
	int	pipes;

	pipes = 0;
	while (token)
	{
		if (*(char *)token->content == '|')
			pipes++;
		token = token->next;
	}
	return (pipes);
}

void	init_pipefd(t_shell *shell)
{
	t_list	*token;
	int		pipes;
	int		i;

	token = shell->token;
	pipes = count_pipes(token);
	i = 0;
	while (i < pipes)
	{
		if (pipe(shell->pipefd[i]) == -1)
		{
			perror("minishell");
			free_struc(shell, 0);
			exit(EXIT_SUCCESS);
		}
		i++;
	}
}

void	close_all_pipefd(t_shell *shell)
{
	t_list	*token;
	int		i;
	int		pipes;

	token = shell->token;
	i = 0;
	pipes = count_pipes(token);
	while (i < pipes)
	{
		if (close(shell->pipefd[i][0]) == -1)
		{
			perror("minishell");
			exit(EXIT_SUCCESS);
		}
		if (close(shell->pipefd[i][1]) == -1)
		{
			perror("minishell");
			exit(EXIT_SUCCESS);
		}
		i++;
	}
}

void	close_all_heredoc_pipe(t_shell *shell)
{
	t_list	*token;
	int		i;

	token = shell->token;
	i = 0;
	while (i < shell->heredoc_pipe_count)
	{
		close(shell->heredocfd[i][0]);
		close(shell->heredocfd[i][1]);
		i++;
	}
}
