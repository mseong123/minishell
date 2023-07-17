/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_unset_builtin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:23:22 by melee             #+#    #+#             */
/*   Updated: 2023/07/12 12:23:29 by melee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_unset_err(char *str)
{
	printf("minishell: unset: '%s': not a valid identifier\n", str);
}

void	parse_unset(char *str)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	if (!ft_isalpha(str[0]))
		error = 1;
	while (str[i])
	{
		if (str[i] < 48 || (str[i] > 57 && str[i] < 65)
			|| (str[i] > 90 && str[i] < 95)
			|| (str[i] > 95 && str[i] < 97) || str[i] > 122)
		{
			error = 1;
			break ;
		}
		i++;
	}
	if (error == 1)
		print_unset_err(str);
}

void	check_unset_builtin(t_child *child, t_list *token)
{
	while (token && ft_strcmp(token->content, "|"))
	{
		if (!ft_strcmp(token->content, "<") || !ft_strcmp(token->content, "<<")
			|| !ft_strcmp(token->content, ">")
			|| !ft_strcmp(token->content, ">>"))
			token = token->next->next;
		else if (!ft_strcmp(token->content, "unset"))
		{
			child->cmd = ft_strdup("unset");
			token = token->next;
		}
		else if (*(char *)token->content == '-')
			token = token->next;
		else
		{
			parse_unset(token->content);
			token = token->next;
		}
	}
}
