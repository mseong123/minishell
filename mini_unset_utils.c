/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:38:58 by melee             #+#    #+#             */
/*   Updated: 2023/07/12 12:39:05 by melee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_env(t_shell *shell, char *str)
{
	int		i;
	int		j;
	char	*key;
	char	**local_envp;

	i = 0;
	j = 0;
	key = ft_strjoin(str, "=");
	local_envp = malloc((count_envp(shell->local_envp)) * sizeof(char *));
	while (shell->local_envp[i])
	{
		if (!ft_strncmp(shell->local_envp[i], key, ft_strlen(key)))
			i++;
		else
			local_envp[j++] = ft_strdup(shell->local_envp[i++]);
	}
	local_envp[j] = NULL;
	i = 0;
	while (shell->local_envp[i])
		free(shell->local_envp[i++]);
	free(shell->local_envp);
	shell->local_envp = local_envp;
	free(key);
}
