/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 11:46:29 by melee             #+#    #+#             */
/*   Updated: 2023/07/14 11:46:37 by melee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initiate_quote(int *quote)
{
	quote[0] = 0;
	quote[1] = 0;
}

void	expand_dollar(t_shell *shell)
{
	char	*str;
	char	*temp;
	char	*res;
	int		quote[2];

	str = shell->line;
	temp = shell->line;
	res = malloc(1 * sizeof(char));
	res[0] = '\0';
	initiate_quote(quote);
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			handle_quote(*str, quote);
		if (*str != '$' || (*str == '$' && quote[1] == 1))
			res = parse_nondollar(res, &str);
		else if (*str == '$' && str[1] == '?' && quote[1] == 0)
			res = parse_exit_status(shell, res, &str);
		else if (*str == '$' && str[1] != '?' && quote[1] == 0)
			res = parse_dollar(shell, res, &str);
	}
	shell->line = res;
	free(temp);
}
