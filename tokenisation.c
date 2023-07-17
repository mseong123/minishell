/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:33:11 by melee             #+#    #+#             */
/*   Updated: 2023/07/03 13:10:19 by melee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_printf(void *content)
{
	printf("%s\n", content);
}

static char	*ft_strndup(const char *s, int size)
{
	int		i;
	char	*result;

	i = 0;
	result = malloc((size + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	while (*s && i < size)
	{
		result[i] = *s++;
		i++;
	}
	result[i] = '\0';
	return (result);
}

void	handle_quote(char c, int *quote)
{
	if (c == '"' && quote[0] == 0 && quote[1] == 0)
		quote[0] = 1;
	else if (c == '\'' && quote[0] == 0 && quote[1] == 0)
		quote[1] = 1;
	else if (c == '"' && quote[0] == 1 && quote[1] == 0)
		quote[0] = 0;
	else if (c == '\'' && quote[1] == 1 && quote[0] == 0)
		quote[1] = 0;
}

void	unclosed_quote(t_shell *shell)
{
	printf("minishell: syntax error : \
unable to locate closing quotation");
	free_struc(shell, 0);
	exit(EXIT_SUCCESS);
}

void	tokenisation(t_shell *shell)
{
	char	*str;
	int		i;
	int		quote[2];

	str = shell->line;
	i = 0;
	quote[0] = 0;
	quote[1] = 0;
	while (*str)
	{
		if (*str == '"' || *str == '\'')
			handle_quote(*str, quote);
		if (*str != ' ' || (*str == ' ' && (quote[0] == 1 || quote[1] == 1)))
			i++;
		else if (*str == ' ' && i != 0 && quote[0] == 0 && quote[1] == 0)
		{
			ft_lstadd_back(&shell->token, ft_lstnew(ft_strndup(str - i, i)));
			i = 0;
		}
		str++;
	}
	if (i != 0)
		ft_lstadd_back(&shell->token, ft_lstnew(ft_strndup(str - i, i)));
	if (quote[0] == 1 || quote[1] == 1)
		unclosed_quote(shell);
}
