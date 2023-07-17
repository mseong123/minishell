/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_export_builtin.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 11:58:40 by melee             #+#    #+#             */
/*   Updated: 2023/07/11 11:58:50 by melee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export_err(char *str)
{
	printf("minishell: export: '%s': not a valid identifier\n", str);
}

void	parse_export(char *str)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	if (!ft_isalpha(str[0]))
		error = 1;
	while (str[i] && str[i] != '=')
	{
		if (str[i] < 48 || (str[i] > 57 && str[i] < 65)
			|| (str[i] > 90 && str[i] < 95) || (str[i] > 95 && str[i] < 97)
			|| str[i] > 122)
		{
			error = 1;
			break ;
		}
		i++;
	}
	if (error == 1)
		print_export_err(str);
}

void	check_export_builtin(t_child *child, t_list *token)
{
	while (token && ft_strcmp(token->content, "|"))
	{
		if (!ft_strcmp(token->content, "<") || !ft_strcmp(token->content, "<<")
			|| !ft_strcmp(token->content, ">")
			|| !ft_strcmp(token->content, ">>"))
			token = token->next->next;
		else if (!ft_strcmp(token->content, "export"))
		{
			child->cmd = ft_strdup("export");
			token = token->next;
		}
		else if (*(char *)token->content == '-')
			token = token->next;
		else
		{
			parse_export(token->content);
			token = token->next;
		}
	}
}
