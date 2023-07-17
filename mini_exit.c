/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:02:14 by melee             #+#    #+#             */
/*   Updated: 2023/07/12 15:02:19 by melee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_exit(t_shell *shell)
{
	t_list	*token;

	token = shell->token;
	while (token && ft_strcmp(token->content, "|"))
	{
		if (!ft_strcmp(token->content, "<") || !ft_strcmp(token->content, "<<")
			|| !ft_strcmp(token->content, ">")
			|| !ft_strcmp(token->content, ">>"))
			token = token->next->next;
		else if (!ft_strcmp(token->content, "exit"))
			return (1);
		else
			return (0);
	}
	return (0);
}

void	mini_exit(t_shell *shell, t_child *child)
{
	t_list	*token;
	int		count;
	int		exit_status;

	token = child->token;
	count = child->count;
	while (token && count)
	{
		if (!ft_strcmp(token->content, "<") || !ft_strcmp(token->content, "<<")
			|| !ft_strcmp(token->content, ">")
			|| !ft_strcmp(token->content, ">>"))
			count = skip2(&token, count);
		else if (!ft_strcmp(token->content, "exit"))
			count = skip1(&token, count);
		else
		{
			exit_status = ft_atoi(token->content);
			free_child(child);
			free_struc(shell, 0);
			exit(exit_status);
		}
	}
	free_child(child);
	free_struc(shell, 0);
	exit(EXIT_SUCCESS);
}

void	wait_exit(t_shell *shell)
{
	t_list	*token;

	token = shell->token;
	if (shell->pid_count == 1 && check_exit(shell))
	{
		printf("exit\n");
		free_struc(shell, 0);
		exit(EXIT_SUCCESS);
	}
}
