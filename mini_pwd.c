/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 19:12:03 by melee             #+#    #+#             */
/*   Updated: 2023/07/10 19:12:11 by melee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_pwd(t_shell *shell, t_child *child)
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
