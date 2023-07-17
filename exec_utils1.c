/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 09:37:34 by melee             #+#    #+#             */
/*   Updated: 2023/07/04 09:56:55 by melee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_file_err(t_shell *shell, t_child *child, char *str)
{
	printf("minishell: %s: No such file or directory\n", str);
	free_child(child);
	free_struc(shell, 0);
	exit(EXIT_FAILURE);
}

t_list	*r_file_init(t_shell *shell, t_child *child, \
t_list *token, int r_fd_count)
{
	char	*filename;

	filename = token->next->content;
	child->r_fd[r_fd_count] = open(filename, O_RDONLY);
	if (child->r_fd[r_fd_count] == -1)
	{
		print_file_err(shell, child, filename);
		free_child(child);
		free_struc(shell, 0);
		exit(EXIT_FAILURE);
	}
	token = token->next->next;
	return (token);
}

t_list	*w_file_init(t_shell *shell, t_child *child, \
t_list *token, int w_fd_count)
{
	char	*filename;

	filename = token->next->content;
	if (!ft_strcmp(token->content, ">>"))
		child->w_fd[w_fd_count] = open(filename, \
		O_CREAT | O_RDWR | O_APPEND, 0666);
	else
		child->w_fd[w_fd_count] = open(filename, \
		O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (child->w_fd[w_fd_count] == -1)
	{
		perror("minishell");
		free_child(child);
		free_struc(shell, 0);
		exit(EXIT_FAILURE);
	}
	token = token->next->next;
	return (token);
}

void	check_w_redirect(t_shell *shell, t_child *child)
{
	t_list	*token;
	int		count;
	int		w_fd_count;

	token = child->token;
	count = child->count;
	w_fd_count = 0;
	while (token && count)
	{
		if (!ft_strcmp(token->content, ">") || !ft_strcmp(token->content, ">>"))
		{
			token = w_file_init(shell, child, token, w_fd_count++);
			count -= 2;
		}
		else
		{
			token = token->next;
			count--;
		}
	}
}

void	check_r_redirect(t_shell *shell, t_child *child)
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
			token = r_file_init(shell, child, token, r_fd_count++);
			count -= 2;
		}
		else
		{
			token = token->next;
			count--;
		}
	}
}
