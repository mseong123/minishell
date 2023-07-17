/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:48:26 by melee             #+#    #+#             */
/*   Updated: 2023/07/13 13:48:46 by melee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_heredoc_quote(int quote)
{
	if (quote == 0)
		return (1);
	else
		return (0);
}

char	*heredoc_expand_dollar(t_shell *shell, char *line)
{
	char	*temp;
	char	*res;

	temp = line;
	res = NULL;
	while (*line)
	{
		if (*line != '$')
			res = parse_nondollar(res, &line);
		else if (*line == '$' && line[1] == '?')
			res = parse_exit_status(shell, res, &line);
		else if (*line == '$' && line[1] != '?')
			res = parse_dollar(shell, res, &line);
	}
	line = res;
	free(temp);
	return (line);
}
