/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 09:18:48 by melee             #+#    #+#             */
/*   Updated: 2023/07/05 09:18:57 by melee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_nonquote(char *res, char **str)
{
	char	*substr;

	if (res == NULL)
	{
		res = malloc(1 * sizeof(char));
		res[0] = '\0';
	}
	substr = ft_substr(*str, 0, 1);
	res = free_substr_join(res, substr);
	*str += 1;
	return (res);
}

void	remove_quotes(t_list *token)
{
	char	*str;
	char	*res;
	int		quote[2];

	str = (char *)token->content;
	res = NULL;
	quote[0] = 0;
	quote[1] = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			handle_quote(*str, quote);
		if ((*str != '"' && *str != '\'') || (*str == '"' && quote[1] == 1)
			|| (*str == '\'' && quote[0] == 1))
			res = parse_nonquote(res, &str);
		else if (*str == '"' || *str == '\'')
			str++;
	}
	if (res == NULL)
	{
		res = malloc(1 * sizeof(char));
		res[0] = '\0';
	}
	free(token->content);
	token->content = res;
}

int	have_enclosed_quotes(t_list *token)
{
	int		i;
	char	*str;
	char	*temp;

	i = 0;
	str = (char *)token->content;
	if ((*str == '"' && str[ft_strlen(str) - 1] == '"')
		|| (*str == '\'' && str[ft_strlen(str) - 1] == '\''))
	{
		temp = ft_substr(str, 1, ft_strlen(str) - 2);
		while (temp[i])
		{
			if (temp[i] == '"' || temp[i] == '\'')
			{
				free(temp);
				return (0);
			}
			i++;
		}
		free(temp);
		return (1);
	}
	return (0);
}

void	remove_enclosed_quotes(t_list *token)
{
	char	*str;

	str = (char *)token->content;
	token->content = ft_substr(str, 1, ft_strlen(str) - 2);
	free(str);
}

char	*ft_getenv(t_shell *shell, char *substr)
{
	int		i;
	char	*res_str;
	char	*concat_equal;

	i = 0;
	concat_equal = ft_strjoin(substr, "=");
	while (shell->local_envp[i])
	{
		if (!strncmp(shell->local_envp[i], concat_equal, \
		ft_strlen(concat_equal)))
		{
			res_str = strchr(shell->local_envp[i], '=');
			res_str++;
			free(concat_equal);
			return (res_str);
		}
		i++;
	}
	free(concat_equal);
	return (NULL);
}
