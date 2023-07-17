/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 19:04:58 by melee             #+#    #+#             */
/*   Updated: 2023/07/06 19:05:11 by melee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_read_fd(t_child *child, int *fd, int count, t_list **token)
{
	dup2(child->r_fd[fd[0]], STDIN_FILENO);
	close(child->r_fd[fd[0]]);
	fd[0] += 1;
	count -= 2;
	*token = (*token)->next->next;
	return (count);
}

int	handle_write_fd(t_child *child, int *fd, int count, t_list **token)
{
	dup2(child->w_fd[fd[1]], STDOUT_FILENO);
	close(child->w_fd[fd[1]]);
	fd[1]++;
	count -= 2;
	*token = (*token)->next->next;
	return (count);
}

int	handle_heredoc_fd(t_shell *shell, int count, t_list **token)
{
	dup2(shell->heredocfd[shell->heredoc_pipe_count][READ_END], STDIN_FILENO);
	shell->heredoc_pipe_count++;
	count -= 2;
	*token = (*token)->next->next;
	return (count);
}

void	set_redirect_fd(t_shell *shell, t_child *child)
{
	t_list	*token;
	int		count;
	int		fd[2];

	token = child->token;
	count = child->count;
	fd[0] = 0;
	fd[1] = 0;
	while (token && count)
	{
		if (!ft_strcmp(token->content, "<"))
			count = handle_read_fd(child, fd, count, &token);
		else if (!ft_strcmp(token->content, ">")
			|| !ft_strcmp(token->content, ">>"))
			count = handle_write_fd(child, fd, count, &token);
		else if (!ft_strcmp(token->content, "<<"))
			count = handle_heredoc_fd(shell, count, &token);
		else
		{
			count--;
			token = token->next;
		}
	}
	close_all_heredoc_pipe(shell);
}
//struct stat file;
//fstat(shell->pipefd[shell->pid_count - 1][READ_END], &file);
//printf("pid %d inode %llu\n", getpid(), file.st_ino);

void	set_pipes(t_shell *shell, t_child *child)
{
	t_list	*token;
	int		count;

	token = child->token;
	count = child->count;
	if (token && token->prev)
	{
		if (dup2(shell->pipefd[shell->pid_count - 2] \
		[READ_END], STDIN_FILENO) == -1)
			perror("minishell");
	}
	while (count)
	{
		token = token->next;
		count--;
	}
	if (token && token->next)
	{
		if (dup2(shell->pipefd[shell->pid_count - 1] \
		[WRITE_END], STDOUT_FILENO) == -1)
			perror("minishell");
	}
	close_all_pipefd(shell);
}
