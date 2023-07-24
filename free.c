/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:46:45 by melee             #+#    #+#             */
/*   Updated: 2023/07/17 11:02:35 by melee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	del(void *content)
{
	free(content);
}

void	free_builtin_bin_path(t_shell *shell, int newline)
{
	int	i;

	i = 0;
	if (shell->builtin_bin_path && !newline)
	{
		while (shell->builtin_bin_path[i])
			free(shell->builtin_bin_path[i++]);
		free(shell->builtin_bin_path);
	}
}

void	free_struc(t_shell *shell, int newline)
{
	int	i;

	i = 0;
	if (shell->line)
		free(shell->line);
	if (shell->token)
		ft_lstclear(&shell->token, del);
	if (shell->bin_path)
	{
		while (shell->bin_path[i])
			free(shell->bin_path[i++]);
		free(shell->bin_path);
	}
	i = 0;
	if (shell->local_envp && !newline)
	{
		while (shell->local_envp[i])
			free(shell->local_envp[i++]);
		free(shell->local_envp);
	}
	free_builtin_bin_path(shell, newline);
}

void	free_child(t_child *child)
{
	if (child->path)
		free(child->path);
	if (child->cmd)
		free(child->cmd);
	if (child->r_fd)
		free(child->r_fd);
	if (child->w_fd)
		free(child->w_fd);
	child->token = NULL;
}
