/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 11:47:07 by melee             #+#    #+#             */
/*   Updated: 2023/07/05 11:47:16 by melee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_pipe_error(t_shell *shell, t_list *token)
{
	int	error;

	error = 0;
	if (*(char *)(token->content) == '|' && token->next == NULL)
		error = 1;
	else if (*(char *)(token->content) == '|' && token->prev == NULL)
		error = 1;
	else if (*(char *)(token->content) == '|'
		&& (token->next && *(char *)token->next->content == '|'))
		error = 1;
	if (error)
	{
		printf("minishell: syntax error near unexpected token '|'\n");
		free_struc(shell, 0);
		exit(EXIT_SUCCESS);
	}
}

void	check_redirec_error(t_shell *shell, t_list *token)
{
	int		error;
	char	*str;
	char	*next_str;

	error = 0;
	str = (char *)token->content;
	if (token->next)
		next_str = (char *)token->next->content;
	if ((!ft_strcmp(str, "<") || !ft_strcmp(str, "<<")
			|| !ft_strcmp(str, ">") || !ft_strcmp(str, ">>"))
		&& token->next == NULL)
		error = 1;
	else if ((!ft_strcmp(str, "<") || !ft_strcmp(str, "<<")
			|| !ft_strcmp(str, ">") || !ft_strcmp(str, ">>"))
		&& next_str && (!ft_strcmp(next_str, "<") || !ft_strcmp(next_str, "<<")
			|| !ft_strcmp(next_str, ">") || !ft_strcmp(next_str, ">>")
			|| !ft_strcmp(next_str, "|")))
		error = 1;
	if (error)
	{
		printf("minishell: syntax error near unexpected token %s\n", str);
		free_struc(shell, 0);
		exit(EXIT_SUCCESS);
	}
}

void	parse_error(t_shell *shell)
{
	t_list	*token;

	token = shell->token;
	while (token)
	{
		check_pipe_error(shell, token);
		token = token->next;
	}
	token = shell->token;
	while (token)
	{
		check_redirec_error(shell, token);
		token = token->next;
	}
}
