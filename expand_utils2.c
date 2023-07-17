/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:56:40 by melee             #+#    #+#             */
/*   Updated: 2023/07/04 13:56:48 by melee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_token(t_list *token, char *str)
{
	t_list	*new_token;

	new_token = ft_lstnew(str);
	if (token->next)
		token->next->prev = new_token;
	new_token->next = token->next;
	new_token->prev = token;
	token->next = new_token;
}

int	expand_d_redirec(char *str, int i, int *quote, t_list *token)
{
	if (((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>'
				&& str[i + 1] == '>')) && quote[0] == 0 && quote[1] == 0
		&& ft_strlen(str) != 2)
	{
		if (i == 0)
		{
			token->content = ft_substr(str, 0, i + 2);
			insert_token(token, ft_substr(str, i + 2, ft_strlen(str)));
			free(str);
			return (1);
		}
		else
		{
			token->content = ft_substr(str, 0, i);
			insert_token(token, ft_substr(str, i, ft_strlen(str)));
			free(str);
			return (1);
		}
	}
	return (0);
}

int	expand_s_redirec(char *str, int i, int *quote, t_list *token)
{
	if (i > 0 && ((str[i] == '<' && str[i + 1] != '<' && str[i - 1] != '<')
			|| (str[i] == '>' && str[i + 1] != '>' && str[i - 1] != '>'))
		&& quote[0] == 0 && quote[1] == 0 && ft_strlen(str) != 1)
	{
		token->content = ft_substr(str, 0, i);
		insert_token(token, ft_substr(str, i, ft_strlen(str)));
		free(str);
		return (1);
	}
	else if (i == 0 && ((str[i] == '<' && str[i + 1] != '<')
			|| (str[i] == '>' && str[i + 1] != '>'))
		&& quote[0] == 0 && quote[1] == 0 && ft_strlen(str) != 1)
	{
		token->content = ft_substr(str, 0, i + 1);
		insert_token(token, ft_substr(str, i + 1, ft_strlen(str)));
		free(str);
		return (1);
	}
	return (0);
}

int	expand_pipe(char *str, int i, int *quote, t_list *token)
{
	if (str[i] == '|' && quote[0] == 0 && quote[1] == 0 && ft_strlen(str) != 1)
	{
		if (i == 0)
		{
			token->content = ft_substr(str, 0, i + 1);
			insert_token(token, ft_substr(str, i + 1, ft_strlen(str)));
			free(str);
			return (1);
		}
		else
		{
			token->content = ft_substr(str, 0, i);
			insert_token(token, ft_substr(str, i, ft_strlen(str)));
			free(str);
			return (1);
		}
	}
	return (0);
}

void	expand_operators(t_list *token)
{
	char	*str;
	int		quote[2];
	int		i;

	str = (char *)token->content;
	quote[0] = 0;
	quote[1] = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			handle_quote(str[i], quote);
		if (expand_d_redirec(str, i, quote, token))
			break ;
		else if (expand_s_redirec(str, i, quote, token))
			break ;
		else if (expand_pipe(str, i, quote, token))
			break ;
		else
			i++;
	}
}
