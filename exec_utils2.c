/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 12:44:44 by melee             #+#    #+#             */
/*   Updated: 2023/07/05 12:44:53 by melee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_slash(char *path, char *input)
{
	char	*res;
	char	*temp;

	temp = ft_strjoin(path, "/");
	res = ft_strjoin(temp, input);
	free(temp);
	return (res);
}

void	check_bin2(t_shell *shell, t_child *child, char *str)
{
	char	*comb_str;
	int		i;

	i = 0;
	while (shell->bin_path[i])
	{
		comb_str = append_slash(shell->bin_path[i], str);
		if (access(comb_str, F_OK | X_OK) == 0)
		{
			child->path = comb_str;
			child->cmd = ft_strdup(str);
		}
		i++;
	}
}

void	check_bin(t_shell *shell, t_child *child, t_list *token)
{
	char	*str;
	char	*comb_str;
	int		i;

	str = (char *)token->content;
	i = 0;
	if (check_builtin(shell, child, token) == 0)
	{
		while (shell->bin_path && shell->bin_path[i] && *str != '\0')
		{
			comb_str = append_slash(shell->bin_path[i], str);
			if (access(comb_str, F_OK | X_OK) == 0)
			{
				child->path = comb_str;
				child->cmd = ft_strdup(str);
			}
			else
				free(comb_str);
			i++;
		}
		if (child->path == NULL)
			print_cmd_err(shell, child, str);
	}
}

void	check_none_bin(t_shell *shell, t_child *child, t_list *token)
{
	char	*str;

	str = (char *)token->content;
	if (access(str, F_OK | X_OK) == -1)
		print_cmd_err(shell, child, str);
	else
	{
		child->path = ft_strdup(str);
		str = strrchr(str, '/');
		str++;
		child->cmd = ft_strdup(str);
	}
}

void	get_cmd(t_shell *shell, t_child *child)
{
	t_list	*token;
	int		count;

	token = child->token;
	count = child->count;
	while (token && count)
	{
		if (!ft_strcmp("<", token->content) || !ft_strcmp("<<", token->content)
			|| !ft_strcmp(">", token->content)
			|| !ft_strcmp(">>", token->content))
		{
			token = token->next->next;
			count -= 2;
		}
		else
		{
			if (strrchr(token->content, '/'))
				check_none_bin(shell, child, token);
			else
				check_bin(shell, child, token);
			break ;
		}
	}
}
