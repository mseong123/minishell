/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:41:51 by melee             #+#    #+#             */
/*   Updated: 2023/07/17 11:32:27 by melee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtin(t_shell *shell, t_child *child, t_list *token)
{
	if (!ft_strcmp(token->content, "cd"))
	{
		check_cd_builtin(shell, child, token);
		return (1);
	}
	else if (!ft_strcmp(token->content, "export"))
	{
		check_export_builtin(child, token);
		return (1);
	}
	else if (!ft_strcmp(token->content, "unset"))
	{
		check_unset_builtin(child, token);
		return (1);
	}
	else if (!ft_strcmp(token->content, "exit"))
	{
		check_exit_builtin(shell, child, token);
		return (1);
	}
	return (0);
}
