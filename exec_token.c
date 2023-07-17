/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:10:24 by melee             #+#    #+#             */
/*   Updated: 2023/07/01 14:10:36 by melee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_child(t_child *child, t_list *token, int count)
{
	child->path = NULL;
	child->cmd = NULL;
	child->count = count;
	child->r_fd = NULL;
	child->w_fd = NULL;
	child->token = token;
	init_read_fd(child);
	init_write_fd(child);
}

void	exec_token(t_shell *shell, t_list *token, int count)
{
	t_child	child;

	if (shell->pid[shell->pid_count - 1] == -1)
	{
		perror("minishell");
		free_struc(shell, 0);
		exit(EXIT_SUCCESS);
	}
	if (shell->pid[shell->pid_count - 1] == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		init_child(&child, token, count);
		check_w_redirect(shell, &child);
		check_r_redirect(shell, &child);
		get_cmd(shell, &child);
		set_pipes(shell, &child);
		set_redirect_fd(shell, &child);
		exec_cmd(shell, &child);
	}
}
