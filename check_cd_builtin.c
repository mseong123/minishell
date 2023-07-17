/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cd_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 11:55:51 by melee             #+#    #+#             */
/*   Updated: 2023/07/11 11:55:59 by melee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cd_err(t_shell *shell, t_child *child, char *str)
{
	printf("minishell: cd: %s: No such file or directory\n", str);
	free_child(child);
	free_struc(shell, 0);
	exit(EXIT_FAILURE);
}

void	check_cd_builtin(t_shell *shell, t_child *child, t_list *token)
{
	while (token && ft_strcmp(token->content, "|"))
	{
		if (!ft_strcmp(token->content, "<") || !ft_strcmp(token->content, "<<")
			|| !ft_strcmp(token->content, ">")
			|| !ft_strcmp(token->content, ">>"))
			token = token->next->next;
		else if (!ft_strcmp(token->content, "cd"))
			token = token->next;
		else if (token->prev && !ft_strcmp(token->prev->content, "cd")
			&& !ft_strcmp(token->content, "-"))
			token = token->next;
		else if (chdir(token->content) == -1)
			print_cd_err(shell, child, token->content);
		else
		{
			child->cmd = ft_strdup("cd");
			break ;
		}
	}
}
