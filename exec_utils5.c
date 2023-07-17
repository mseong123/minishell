/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 12:01:30 by melee             #+#    #+#             */
/*   Updated: 2023/07/07 12:01:38 by melee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip1(t_list **token, int count)
{
	*token = (*token)->next;
	count -= 1;
	return (count);
}

int	skip2(t_list **token, int count)
{
	*token = (*token)->next->next;
	count -= 2;
	return (count);
}

int	count_cmd_str(t_child *child)
{
	t_list	*token;
	int		count;
	int		count_cmd_str;

	token = child->token;
	count = child->count;
	count_cmd_str = 0;
	while (token && count)
	{
		if (!ft_strcmp(token->content, "<") || !ft_strcmp(token->content, "<<")
			|| !ft_strcmp(token->content, ">")
			|| !ft_strcmp(token->content, ">>"))
			count = skip2(&token, count);
		else
		{
			token = token->next;
			count--;
			count_cmd_str++;
		}
	}
	return (count_cmd_str);
}

char	**pop_cmd_str(t_child *child)
{
	t_list	*token;
	int		count;
	char	**cmd_str;
	int		i;

	token = child->token;
	count = child->count;
	cmd_str = malloc((count_cmd_str(child) + 1) * sizeof(char *));
	i = 0;
	while (token && count)
	{
		if (!ft_strcmp(token->content, "<") || !ft_strcmp(token->content, "<<")
			|| !ft_strcmp(token->content, ">")
			|| !ft_strcmp(token->content, ">>"))
			count = skip2(&token, count);
		else
		{
			cmd_str[i++] = token->content;
			token = token->next;
			count--;
		}
	}
	cmd_str[i] = NULL;
	return (cmd_str);
}

void	exec_cmd(t_shell *shell, t_child *child)
{
	char	**cmd_str;

	if (child->cmd && !ft_strcmp(child->cmd, "echo"))
		mini_echo(shell, child);
	else if (child->cmd && !ft_strcmp(child->cmd, "cd"))
		mini_cd(shell, child);
	else if (child->cmd && !ft_strcmp(child->cmd, "pwd"))
		mini_pwd(shell, child);
	else if (child->cmd && !ft_strcmp(child->cmd, "env"))
		mini_env(shell, child);
	else if (child->cmd && !ft_strcmp(child->cmd, "export"))
		mini_export(shell, child);
	else if (child->cmd && !ft_strcmp(child->cmd, "exit"))
		mini_exit(shell, child);
	else
	{
		cmd_str = pop_cmd_str(child);
		if (execve(child->path, cmd_str, shell->local_envp) == -1)
		{
			free(cmd_str);
			free_child(child);
			free_struc(shell, 0);
			exit(EXIT_SUCCESS);
		}
	}
}
