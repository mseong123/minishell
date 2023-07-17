/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exit_builtin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:43:38 by melee             #+#    #+#             */
/*   Updated: 2023/07/12 14:43:44 by melee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_exit_err(t_shell *shell, t_child *child, char *str)
{
	printf("minishell: exit: %s: numeric argument required\n", str);
	free_child(child);
	free_struc(shell, 0);
	exit(255);
}

void	print_exit_err2(t_shell *shell, t_child *child)
{
	printf("minishell: exit: too many arguments\n");
	free_child(child);
	free_struc(shell, 0);
	exit(EXIT_FAILURE);
}

void	parse_exit(t_shell *shell, t_child *child, char *str)
{
	int	i;

	i = 0;
	if (ft_atoi(str) == 0 && *str != '0')
		print_exit_err(shell, child, str);
}

void	check_exit_builtin(t_shell *shell, t_child *child, t_list *token)
{
	int	arg;

	arg = 0;
	while (token && ft_strcmp(token->content, "|"))
	{
		if (!ft_strcmp(token->content, "<") || !ft_strcmp(token->content, "<<")
			|| !ft_strcmp(token->content, ">")
			|| !ft_strcmp(token->content, ">>"))
			token = token->next->next;
		else if (!ft_strcmp(token->content, "exit"))
		{
			child->cmd = ft_strdup("exit");
			token = token->next;
		}
		else if (arg == 0)
		{
			parse_exit(shell, child, token->content);
			arg = 1;
			token = token->next;
		}
		else if (arg == 1)
			print_exit_err2(shell, child);
	}
}
