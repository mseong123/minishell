/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:37:00 by melee             #+#    #+#             */
/*   Updated: 2023/07/11 17:37:10 by melee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_env(t_shell *shell, char *str)
{
	int		i;
	char	**local_envp;

	i = 0;
	local_envp = malloc((count_envp(shell->local_envp) + 2) * sizeof(char *));
	while (shell->local_envp[i])
	{
		local_envp[i] = ft_strdup(shell->local_envp[i]);
		i++;
	}
	local_envp[i++] = ft_strdup(str);
	local_envp[i] = NULL;
	i = 0;
	while (shell->local_envp[i])
		free(shell->local_envp[i++]);
	free(shell->local_envp);
	shell->local_envp = local_envp;
}
