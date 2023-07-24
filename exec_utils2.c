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

char	**check_bin_path(t_shell *shell, char *str)
{
	if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "pwd"))
		return (shell->builtin_bin_path);
	else
		return (shell->bin_path);
}

void	check_bin(t_shell *shell, t_child *child, t_list *token)
{
	char	*comb_str;
	int		i;
	char	**bin_path;

	i = 0;
	bin_path = check_bin_path(shell, token->content);
	if (check_builtin(shell, child, token) == 0)
	{
		while (bin_path && bin_path[i] && *(char *)token->content != '\0')
		{
			comb_str = append_slash(bin_path[i], token->content);
			if (access(comb_str, F_OK | X_OK) == 0)
			{
				child->path = comb_str;
				child->cmd = ft_strdup(token->content);
			}
			else
				free(comb_str);
			i++;
		}
		if (child->path == NULL)
			print_cmd_err(shell, child, token->content);
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
		str = ft_strrchr(str, '/');
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
			if (ft_strrchr(token->content, '/'))
				check_none_bin(shell, child, token);
			else
				check_bin(shell, child, token);
			break ;
		}
	}
}
