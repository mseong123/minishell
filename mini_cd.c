/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 13:36:59 by melee             #+#    #+#             */
/*   Updated: 2023/07/17 11:02:56 by melee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_cd(t_shell *shell, t_child *child)
{
	free_child(child);
	free_struc(shell, 0);
	exit(EXIT_SUCCESS);
}

int	check_cd(t_shell *shell)
{
	t_list	*token;

	token = shell->token;
	while (token && ft_strcmp(token->content, "|"))
	{
		if (!ft_strcmp(token->content, "<") || !ft_strcmp(token->content, "<<")
			|| !ft_strcmp(token->content, ">")
			|| !ft_strcmp(token->content, ">>"))
			token = token->next->next;
		else if (!ft_strcmp(token->content, "cd"))
			return (1);
		else
			return (0);
	}
	return (0);
}

char	*get_cd(t_shell *shell)
{
	t_list	*token;

	token = shell->token;
	while (token && ft_strcmp(token->content, "|"))
	{
		if (!ft_strcmp(token->content, "<") || !ft_strcmp(token->content, "<<")
			|| !ft_strcmp(token->content, ">")
			|| !ft_strcmp(token->content, ">>"))
			token = token->next->next;
		else if (!ft_strcmp(token->content, "cd"))
			token = token->next;
		else
			return (token->content);
	}
	return (NULL);
}

void	set_home(t_shell *shell)
{
	char	*home_path;
	int		set_home;
	int		i;

	set_home = 0;
	i = 0;
	while (shell->local_envp[i])
	{
		if (!ft_strncmp(shell->local_envp[i], "HOME=", ft_strlen("HOME=")))
		{
			home_path = ft_strchr(shell->local_envp[i], '=');
			home_path++;
			chdir(home_path);
			set_home = 1;
		}
		i++;
	}
	if (!set_home)
		printf("bash: cd: HOME not set\n");
}

void	wait_cd(t_shell *shell)
{
	if (shell->pid_count == 1 && check_cd(shell)
		&& WIFEXITED(shell->exit_status)
		&& WEXITSTATUS(shell->exit_status) == EXIT_SUCCESS)
	{
		if (get_cd(shell) == NULL)
			set_home(shell);
		else
			chdir(get_cd(shell));
	}
}
