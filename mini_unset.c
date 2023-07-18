/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:58:11 by melee             #+#    #+#             */
/*   Updated: 2023/07/12 11:58:18 by melee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_unset(t_shell *shell)
{
	t_list	*token;

	token = shell->token;
	while (token && ft_strcmp(token->content, "|"))
	{
		if (!ft_strcmp(token->content, "<") || !ft_strcmp(token->content, "<<")
			|| !ft_strcmp(token->content, ">")
			|| !ft_strcmp(token->content, ">>"))
			token = token->next->next;
		else if (!ft_strcmp(token->content, "unset"))
			return (1);
		else
			return (0);
	}
	return (0);
}

int	parse_unset_error(char *str)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	if (!ft_isalpha(str[0]))
		return (1);
	while (str[i])
	{
		if (str[i] < 48 || (str[i] > 57 && str[i] < 65)
			|| (str[i] > 90 && str[i] < 95) || (str[i] > 95 && str[i] < 97)
			|| str[i] > 122)
			return (1);
		i++;
	}
	return (0);
}

void	unset_env(t_shell *shell, char *str)
{
	int		i;
	int		to_unset;
	char	*key;

	i = 0;
	to_unset = 0;
	key = ft_strjoin(str, "=");
	while (shell->local_envp[i])
	{
		if (!ft_strncmp(shell->local_envp[i], key, ft_strlen(key)))
			to_unset = 1;
		i++;
	}
	if (to_unset)
		remove_env(shell, str);
	free(key);
}

void	wait_unset(t_shell *shell)
{
	t_list	*token;

	token = shell->token;
	if (shell->pid_count == 1 && check_unset(shell))
	{
		while (token && ft_strcmp(token->content, "|"))
		{
			if (!ft_strcmp(token->content, "<")
				|| !ft_strcmp(token->content, "<<")
				|| !ft_strcmp(token->content, ">")
				|| !ft_strcmp(token->content, ">>"))
				token = token->next->next;
			else if (!ft_strcmp(token->content, "unset"))
				token = token->next;
			else if (*(char *)token->content == '-')
				token = token->next;
			else if (parse_unset_error(token->content))
				token = token->next;
			else
			{
				unset_env(shell, token->content);
				token = token->next;
			}
		}
	}
}
