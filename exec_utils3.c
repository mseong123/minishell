/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:24:58 by melee             #+#    #+#             */
/*   Updated: 2023/07/06 09:33:51 by melee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd_err(t_shell *shell, t_child *child, char *str)
{
	printf("minishell: %s: command not found\n", str);
	free_child(child);
	free_struc(shell, 0);
	exit(127);
}

void	init_write_fd2(t_child *child, int w_fd_count)
{
	int	i;

	i = 0;
	if (w_fd_count > 0)
	{
		child->w_fd = malloc((w_fd_count + 1) * sizeof(int));
		while (i < w_fd_count + 1)
			child->w_fd[i++] = -2;
	}
}

void	init_write_fd(t_child *child)
{
	t_list	*token;
	int		count;
	int		w_fd_count;

	token = child->token;
	count = child->count;
	w_fd_count = 0;
	while (token && count)
	{
		if (!ft_strcmp(token->content, ">>")
			|| (!ft_strcmp(token->content, ">")))
		{
			w_fd_count++;
			count -= 2;
			token = token->next->next;
		}
		else
		{
			count--;
			token = token->next;
		}
	}
	init_write_fd2(child, w_fd_count);
}

void	init_read_fd2(t_child *child, int r_fd_count)
{
	int	i;

	i = 0;
	if (r_fd_count > 0)
	{
		child->r_fd = malloc((r_fd_count + 1) * sizeof(int));
		while (i < r_fd_count + 1)
			child->r_fd[i++] = -2;
	}
}

void	init_read_fd(t_child *child)
{
	t_list	*token;
	int		count;
	int		r_fd_count;

	token = child->token;
	count = child->count;
	r_fd_count = 0;
	while (token && count)
	{
		if (!ft_strcmp(token->content, "<"))
		{
			r_fd_count++;
			count -= 2;
			token = token->next->next;
		}
		else
		{
			count--;
			token = token->next;
		}
	}
	init_read_fd2(child, r_fd_count);
}
