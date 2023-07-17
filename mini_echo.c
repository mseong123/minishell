/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:19:27 by melee             #+#    #+#             */
/*   Updated: 2023/07/10 11:20:02 by melee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_redirect(char *str)
{
	if (!ft_strcmp(str, "<") || !ft_strcmp(str, "<<")
		|| !ft_strcmp(str, ">") || !ft_strcmp(str, ">>"))
		return (1);
	else
		return (0);
}

int	if_n_echo(t_list *token)
{
	if (!ft_strcmp(token->content, "-n")
		&& token->prev && !ft_strcmp(token->prev->content, "echo"))
		return (1);
	else
		return (0);
}

int	count_echo_str(t_list *token, int count)
{
	int	count_cmd_str;
	int	flag;

	count_cmd_str = 0;
	flag = 0;
	while (token && count)
	{
		if (if_redirect(token->content))
			count = skip2(&token, count);
		else if (if_n_echo(token))
		{
			count = skip1(&token, count);
			count_cmd_str++;
			flag = 1;
		}
		else if (!ft_strcmp(token->content, "-n") && flag)
			count = skip1(&token, count);
		else
		{
			count = skip1(&token, count);
			count_cmd_str++;
			flag = 0;
		}
	}
	return (count_cmd_str);
}

char	**pop_echo_str(t_list *token, int count, char **cmd_str, int flag)
{
	int	i;

	i = 0;
	while (token && count)
	{
		if (if_redirect(token->content))
			count = skip2(&token, count);
		else if (!ft_strcmp(token->content, "-n")
			&& token->prev && !ft_strcmp(token->prev->content, "echo"))
		{
			cmd_str[i++] = token->content;
			count = skip1(&token, count);
			flag = 1;
		}
		else if (!ft_strcmp(token->content, "-n") && flag)
			count = skip1(&token, count);
		else
		{
			cmd_str[i++] = token->content;
			count = skip1(&token, count);
			flag = 0;
		}
	}
	cmd_str[i] = NULL;
	return (cmd_str);
}

void	mini_echo(t_shell *shell, t_child *child)
{
	t_list	*token;
	int		count;
	char	**cmd_str;

	token = child->token;
	count = child->count;
	cmd_str = malloc((count_echo_str(token, count) + 1) * sizeof(char *));
	cmd_str = pop_echo_str(token, count, cmd_str, 0);
	if (execve(child->path, cmd_str, shell->local_envp) == -1)
	{
		free(cmd_str);
		free_child(child);
		free_struc(shell, 0);
		exit(EXIT_SUCCESS);
	}
}
