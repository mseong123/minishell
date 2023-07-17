/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 11:45:14 by melee             #+#    #+#             */
/*   Updated: 2023/07/11 11:45:21 by melee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_any_export_arg(t_list *token, int count)
{
	while (token && count)
	{
		if (!ft_strcmp(token->content, "<") || !ft_strcmp(token->content, "<<")
			|| !ft_strcmp(token->content, ">")
			|| !ft_strcmp(token->content, ">>"))
			count = skip2(&token, count);
		else if (!ft_strcmp(token->content, "export"))
			count = skip1(&token, count);
		else
			return (1);
	}
	return (0);
}

void	change_to_env(t_shell *shell, t_child *child)
{
	char	*comb_str;
	int		i;

	i = 0;
	while (shell->bin_path[i])
	{
		comb_str = append_slash(shell->bin_path[i], "env");
		if (access(comb_str, F_OK | X_OK) == 0)
		{
			child->path = comb_str;
			child->cmd = ft_strdup("env");
		}
		else
			free(comb_str);
		i++;
	}
}

void	mini_export(t_shell *shell, t_child *child)
{
	char	**cmd_str;

	if (!check_any_export_arg(child->token, child->count))
	{
		change_to_env(shell, child);
		cmd_str = malloc(2 * sizeof(char *));
		cmd_str[0] = child->cmd;
		cmd_str[1] = NULL;
		if (execve(child->path, cmd_str, shell->local_envp) == -1)
		{
			free(cmd_str[0]);
			free(cmd_str);
			free_child(child);
			free_struc(shell, 0);
			exit(EXIT_SUCCESS);
		}
	}
	else
	{
		free_child(child);
		free_struc(shell, 0);
		exit(EXIT_SUCCESS);
	}
}
