/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 09:04:17 by melee             #+#    #+#             */
/*   Updated: 2023/07/17 10:40:28 by melee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	have_middle_quotes(t_list *token)
{
	int		i;
	char	*str;

	i = 1;
	str = (char *)token->content;
	while (i < (int)ft_strlen(str) - 1)
	{
		if (str[i] == '"' || str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

t_list	*remove_token(t_shell *shell, t_list *token)
{
	char	*str;
	t_list	*temp_token;

	str = (char *)token->content;
	if (*str == '\0')
	{
		if (token->next)
			token->next->prev = token->prev;
		if (token->prev)
			token->prev->next = token->next;
		temp_token = token;
		if (!temp_token->prev && !temp_token->next)
			shell->token = NULL;
		if (!temp_token->prev && temp_token->next)
			shell->token = temp_token->next;
		token = token->next;
		ft_lstdelone(temp_token, del);
	}
	else
		token = token->next;
	return (token);
}

void	expand_token2(t_shell *shell)
{
	t_list	*token;
	int		middle_quotes;
	int		enclosed_quotes;

	token = shell->token;
	while (token)
	{
		enclosed_quotes = have_enclosed_quotes(token);
		if (enclosed_quotes)
			remove_enclosed_quotes(token);
		token = token->next;
	}
	token = shell->token;
	while (token)
	{
		middle_quotes = have_middle_quotes(token);
		if (middle_quotes)
			remove_quotes(token);
		token = token->next;
	}
}
//ft_lstiter(shell->token, ft_printf);

void	expand_token(t_shell *shell)
{
	t_list	*token;

	token = shell->token;
	while (token)
	{
		expand_operators(token);
		token = token->next;
	}
	token = shell->token;
	while (token)
		token = remove_token(shell, token);
	expand_token2(shell);
}
