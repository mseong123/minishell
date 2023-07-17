/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 10:59:40 by melee             #+#    #+#             */
/*   Updated: 2023/07/17 10:45:08 by melee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_arg(t_list *token)
{
	int	count;

	count = 0;
	while (token)
	{
		if (*(char *)token->content == '|')
			break ;
		count++;
		token = token->next;
	}
	return (count);
}

void	heredoc_pipe_count(t_shell *shell, t_list *token)
{
	while (token && *(char *)token->content != '|')
	{
		if (!ft_strcmp(token->content, "<<"))
			shell->heredoc_pipe_count++;
		token = token->next;
	}
}

void	parse_token(t_shell *shell)
{
	t_list	*token;
	int		count;

	token = shell->token;
	count = 0;
	init_pipefd(shell);
	while (token)
	{
		count = count_arg(token);
		if (count > 0)
		{
			shell->pid_count++;
			shell->pid[shell->pid_count - 1] = fork();
			exec_token(shell, token, count);
		}
		heredoc_pipe_count(shell, token);
		while (count--)
			token = token->next;
		if (token && *(char *)(token->content) == '|')
			token = token->next;
	}
	close_all_pipefd(shell);
	close_all_heredoc_pipe(shell);
}
