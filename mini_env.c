/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 08:13:50 by melee             #+#    #+#             */
/*   Updated: 2023/07/17 10:41:57 by melee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_env(t_shell *shell, t_child *child)
{
	char	**cmd_str;

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
