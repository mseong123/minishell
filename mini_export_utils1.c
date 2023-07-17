/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:22:00 by melee             #+#    #+#             */
/*   Updated: 2023/07/11 14:22:08 by melee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_export(t_shell *shell)
{
	t_list	*token;

	token = shell->token;
	while (token && ft_strcmp(token->content, "|"))
	{
		if (!ft_strcmp(token->content, "<") || !ft_strcmp(token->content, "<<")
			|| !ft_strcmp(token->content, ">")
			|| !ft_strcmp(token->content, ">>"))
			token = token->next->next;
		else if (!ft_strcmp(token->content, "export"))
			return (1);
		else
			return (0);
	}
	return (0);
}

int	parse_export_error(char *str)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	if (!ft_isalpha(str[0]))
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (str[i] < 48 || (str[i] > 57 && str[i] < 65)
			|| (str[i] > 90 && str[i] < 95) || (str[i] > 95 && str[i] < 97)
			|| str[i] > 122)
			return (1);
		i++;
	}
	return (0);
}

char	*parse_key(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	i++;
	return (ft_substr(str, 0, i));
}

void	export_env(t_shell *shell, char *str)
{
	int		i;
	char	*key;
	int		parsed;

	i = 0;
	key = parse_key(str);
	parsed = 0;
	while (shell->local_envp[i])
	{
		if (!strncmp(shell->local_envp[i], key, ft_strlen(key)))
		{
			free(shell->local_envp[i]);
			shell->local_envp[i] = ft_strdup(str);
			parsed = 1;
			break ;
		}
		i++;
	}
	if (!parsed)
		insert_env(shell, str);
	free(key);
}

void	wait_export(t_shell *shell)
{
	t_list	*token;

	token = shell->token;
	if (shell->pid_count == 1 && check_export(shell))
	{
		while (token && ft_strcmp(token->content, "|"))
		{
			if (if_redirect(token->content))
				token = token->next->next;
			else if (!ft_strcmp(token->content, "export"))
				token = token->next;
			else if (*(char *)token->content == '-')
				token = token->next;
			else if (parse_export_error(token->content)
				|| ft_strchr(token->content, '=') == NULL)
				token = token->next;
			else
			{
				export_env(shell, token->content);
				token = token->next;
			}
		}
	}
}
